// Fill out your copyright notice in the Description page of Project Settings.


#include "EspiritaCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "Espirita/EspiritaGameModeBase.h"
#include "Espirita/Enemies/StandardEnemy.h"
#include "Espirita/EscenaryObjects/Doors/Door.h"


#define TIMERCALLING 0.1f
#define PLAYING 0
#define WIN 1
#define LOSE -1
//////////////////////////////////////////////////////////////////////////
// AEspiritaCharacter

AEspiritaCharacter::AEspiritaCharacter()
{
	//pause flag
	onPause = true;
	currTime = 0;
	//PickUp flag
	canInteract = false;
	//Set the camera debug variables
	isFixedCamera = false;
	cameraAngle = -70.0f;
	cameraLengthToPlayer = 600.0f;
	//collec default time
	timeToCollet = 2.0f;
	canPick = false;
	timerCalls = 0.0f;
	//block variables
	blockDistanceFromThePlayer = 200.0f;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = cameraLengthToPlayer;
	CameraBoom->RelativeRotation = FRotator(cameraAngle, 0.f, 0.f);
	CameraBoom->bAbsoluteLocation = isFixedCamera; //Don't want arm to move, is fixed camera
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}
//////////////////////////////////////////////////////////////////////////
// Input

void AEspiritaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &AEspiritaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEspiritaCharacter::MoveRight);

	FInputActionBinding& toggle = InputComponent->BindAction("RestartLevel", IE_Pressed, this, &AEspiritaCharacter::RestartLevel);
	toggle.bExecuteWhenPaused = true;
	//PickUp the items
	InputComponent->BindAction("PutBlock", IE_Pressed, this, &AEspiritaCharacter::PutBlock);

	InputComponent->BindAction("PickUp", IE_Pressed, this, &AEspiritaCharacter::Interact);
	InputComponent->BindAction("PickUp", IE_Released, this, &AEspiritaCharacter::StopInteract);

}

void AEspiritaCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Collision functions
	OnActorHit.AddDynamic(this, &AEspiritaCharacter::OnHit);
	OnActorBeginOverlap.AddDynamic(this, &AEspiritaCharacter::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &AEspiritaCharacter::EndOverlap);
	//Get world()
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	//set camera variables
	CameraBoom->bAbsoluteLocation = isFixedCamera; //Don't want arm to move, is fixed camera
	gameMode->angle = cameraAngle;
	gameMode->distance = cameraLengthToPlayer;
}

void AEspiritaCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);


	if (canPick && canInteract)
	{
		timerCalls += deltaTime;
		if (timerCalls >= timeToCollet)
		{
			Pick();
			timerCalls = 0.0f;
		}
	}

}

void AEspiritaCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEspiritaCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AEspiritaCharacter::RestartLevel()
{
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	if (gameMode->actualGameState != PLAYING) {
		GetWorld()->ServerTravel(gameMode->GetName());
	}
}

void AEspiritaCharacter::OnOverlap(AActor* me, AActor* other)
{
	IInteroperable* interacting = Cast<IInteroperable>(other);
	if (interacting != nullptr)
	{
		canInteract = true;	
		interactObject = interacting;
		interacting = nullptr;
	}
}
void AEspiritaCharacter::EndOverlap(AActor* me, AActor* other)
{
	if (Cast<IInteroperable>(other) != nullptr)
	{
		canInteract = false;
		interactObject = nullptr;
	}
}

void AEspiritaCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AStandardEnemy* overalpObject = Cast<AStandardEnemy>(OtherActor);
	if (overalpObject != nullptr) {
		gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
		gameMode->actualGameState = LOSE;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
void AEspiritaCharacter::Interact()
{
	canPick = true;
	ADoor* someDoor = Cast<ADoor>(interactObject);


	interactObject->DoPlayerInteraction();
	
	/*if (canInteract && (interactObject != nullptr && someDoor != nullptr))
	{
		interactObject->DoPlayerInteraction();
	}
	else if (canInteract && (interactObject != nullptr || someDoor == nullptr))
	{
		canPick = true;
	}*/
}

void AEspiritaCharacter::PutBlock()
{
	if (blockToSpawn != nullptr)
	{
		const FRotator actorRotation = GetActorRotation();
		const FVector  actorPosition = GetActorLocation();
		const FVector  forwarVector = GetActorForwardVector() * blockDistanceFromThePlayer;
		const FVector  blockPosition = actorPosition + forwarVector;

		if (currentBlock == nullptr)
		{
			currentBlock = GetWorld()->SpawnActor<ABlock>(blockToSpawn, blockPosition, actorRotation);
			return;
		}
		currentBlock->SetActorLocation(blockPosition);
		currentBlock->SetActorRotation(actorRotation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT BLOCK"));
	}
}
void AEspiritaCharacter::StopInteract()
{
	canPick = false;
	timerCalls = 0.0f;
}

void AEspiritaCharacter::Pick()
{
	if (canPick && canInteract && interactObject != nullptr)
	{
		interactObject->DoPlayerInteraction();
	}
}