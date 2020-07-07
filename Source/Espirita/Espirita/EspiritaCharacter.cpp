// Fill out your copyright notice in the Description page of Project Settings.
#include "EspiritaCharacter.h"
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

#define PLAYING 0
#define WIN 1
#define LOSE -1

FTimerHandle RunValidationTimerHandle;

AEspiritaCharacter::AEspiritaCharacter()
{
	CanInteract = false;
	IsRunning = false;
	IsFixedCamera = true;
	RunSpeedMultiplier = 2.0F;
	CameraAngle = -90.0f;
	CameraLengthToPlayer = 1000.0f;
	BlockDistanceFromThePlayer = 250.0f;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	Movement = GetCharacterMovement();
	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = CameraLengthToPlayer;
	CameraBoom->SetRelativeRotation(FRotator(CameraAngle, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteLocation(IsFixedCamera);
	CameraBoom->bDoCollisionTest = false;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	RunSoulCost = 0.1F;
	SummonSoulCost = 1.0F;
}

void AEspiritaCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AEspiritaCharacter::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &AEspiritaCharacter::EndOverlap);

	GameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();

	BaseMovementSpeed = Movement->MaxWalkSpeed;
	GetWorld()->GetTimerManager().SetTimer(RunValidationTimerHandle, this, &AEspiritaCharacter::ValidateRun, 0.25F, true, 0.0f);
}

void AEspiritaCharacter::ValidateRun()
{
	if (IsRunning)
		Movement->MaxWalkSpeed = (BaseMovementSpeed * RunSpeedMultiplier);
	else
		Movement->MaxWalkSpeed = BaseMovementSpeed;

	if (IsRunning && !GameMode->TrySpendEnergy(RunSoulCost))
		TryStopRun();
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

void AEspiritaCharacter::DoInteraction()
{
	if (InteractObject) 
		InteractObject->DoPlayerInteraction();
}

void AEspiritaCharacter::EndGame()
{
	GameMode->ActualGameState = LOSE;
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AEspiritaCharacter::TrySummonBlock()
{
	if (!bIsRemoving && !bIsCasting)
	{
		if (CurrentBlock != nullptr)
		{
			bIsRemoving = true;
			CurrentBlock->RemoveBlock();
			RemoveBlock(CurrentBlock->GetActorLocation());
			CurrentBlock = nullptr;
		}
		else if (GameMode->TrySpendEnergy(SummonSoulCost))
			SummonBlock();
	}
}

void AEspiritaCharacter::ClearCurrentBlock()
{
	bIsRemoving = false;

	if (CurrentBlock != nullptr && IsValid(CurrentBlock) && !CurrentBlock->IsPendingKill())
		CurrentBlock->Destroy();

	CurrentBlock = nullptr;
}

void AEspiritaCharacter::BlockRemoveEnded()
{
	bIsRemoving = false;
}

void AEspiritaCharacter::PutBlock()
{
	if (bIsCasting && IsValid(BlockToSpawn))
	{
		const FRotator actorRotation = GetActorRotation();
		const FVector  actorPosition = GetActorLocation();
		const FVector  forwarVector = GetActorForwardVector() * BlockDistanceFromThePlayer;
		const FVector  blockPosition = actorPosition + forwarVector;

		if (CurrentBlock == nullptr)
		{
			CurrentBlock = GetWorld()->SpawnActor<ABlock>(BlockToSpawn, blockPosition, actorRotation);
			CurrentBlock->SpawnBlock();
			return;
		}

		CurrentBlock->SetActorLocation(blockPosition);
		CurrentBlock->SetActorRotation(actorRotation);
		CurrentBlock->SpawnBlock();
	}
}

void AEspiritaCharacter::TryStartRun()
{
	if (GameMode->GetCurrentEnergy() > RunSoulCost)
		IsRunning = true;
}

void AEspiritaCharacter::TryStopRun()
{
	IsRunning = false;
}
