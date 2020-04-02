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
#include "Espirita/EspiritaInterfaces/Interoperable.h"


#define TIMERCALLING 0.1f
#define PLAYING 0
#define WIN 1
#define LOSE -1
//////////////////////////////////////////////////////////////////////////
// AEspiritaCharacter

AEspiritaCharacter::AEspiritaCharacter()
{
	//pause flag
	OnPause = true;
	CurrTime = 0;
	//PickUp flag
	CanInteract = false;
	//Set the camera debug variables
	IsFixedCamera = true;
	CameraAngle = -70.0f;
	CameraLengthToPlayer = 600.0f;
	//collec default time
	TimeToCollet = 2.0f;
	TimerCalls = 0.0f;
	//block variables
	BlockDistanceFromThePlayer = 250.0f;

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
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = CameraLengthToPlayer;
	CameraBoom->SetRelativeRotation(FRotator(CameraAngle, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteLocation(IsFixedCamera); //Don't want arm to move, is fixed camera
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}
//////////////////////////////////////////////////////////////////////////
// Input


void AEspiritaCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Collision functions
	OnActorHit.AddDynamic(this, &AEspiritaCharacter::OnHit);
	OnActorBeginOverlap.AddDynamic(this, &AEspiritaCharacter::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &AEspiritaCharacter::EndOverlap);
	//Get world()
	GameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	//set camera variables
	CameraBoom->SetUsingAbsoluteLocation(IsFixedCamera); //Don't want arm to move, is fixed camera
	GameMode->angle = CameraAngle;
	GameMode->distance = CameraLengthToPlayer;
}

void AEspiritaCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AEspiritaCharacter::OnOverlap(AActor* me, AActor* other)
{
	IInteroperable* interacting = Cast<IInteroperable>(other);
	if (interacting != nullptr)
	{
		CanInteract = true;	
		InteractObject = interacting;
		interacting = nullptr;
	}
}
void AEspiritaCharacter::EndOverlap(AActor* me, AActor* other)
{
	if (Cast<IInteroperable>(other) != nullptr)
	{
		CanInteract = false;
		InteractObject = nullptr;
	}
}

void AEspiritaCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AStandardEnemy* overalpObject = Cast<AStandardEnemy>(OtherActor);
	if (overalpObject != nullptr) {
		GameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
		GameMode->actualGameState = LOSE;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AEspiritaCharacter::DoInteraction()
{
	//if(IsValid(InteractObject))
	if (InteractObject) 
	{
		InteractObject->DoPlayerInteraction();

	}	
}
