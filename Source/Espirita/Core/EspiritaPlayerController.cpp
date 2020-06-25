// Fill out your copyright notice in the Description page of Project Settings.

#include "EspiritaPlayerController.h"
#include "Espirita/Espirita/EspiritaCharacter.h"
#include "Espirita/EspiritaGameModeBase.h"
#include "Kismet/GameplayStatics.h"

#define PLAYING 0
#define WIN 1
#define LOSE -1

void AEspiritaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AEspiritaCharacter>(GetPawn());
}

void AEspiritaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	SetUpInput();
}

void AEspiritaPlayerController::SetUpInput()
{
	InputComponent->BindAxis("MoveForward", this, &AEspiritaPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AEspiritaPlayerController::MoveRight);
	InputComponent->BindAction("PutBlock", IE_Pressed, this, &AEspiritaPlayerController::PutBlock);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AEspiritaPlayerController::Interact);
	InputComponent->BindAction("Interact", IE_Released, this, &AEspiritaPlayerController::StopInteract);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AEspiritaPlayerController::StartRun);
	InputComponent->BindAction("Sprint", IE_Released, this, &AEspiritaPlayerController::StopRun);
	FInputActionBinding& toggle = InputComponent->BindAction("RestartLevel", IE_Released, this, &AEspiritaPlayerController::TryRestartLevel);
	toggle.bExecuteWhenPaused = true;
}

void AEspiritaPlayerController::MoveForward(float Value)
{
	if ((Value != 0.0f) && IsValid(Player))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Player->AddMovementInput(Direction, Value);
	}
}

void AEspiritaPlayerController::MoveRight(float Value)
{
	if ((Value != 0.0f) && IsValid(Player))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		Player->AddMovementInput(Direction, Value);
	}
}

void AEspiritaPlayerController::TryRestartLevel()
{
	AEspiritaGameModeBase * gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();

	if (gameMode->actualGameState != PLAYING) 
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}

void AEspiritaPlayerController::PutBlock()
{
	if (IsValid(Player) && !Player->bIsCasting)
		Player->InvokeBlock();
}

void AEspiritaPlayerController::StopInteract()
{
	if (IsValid(Player)) 
		Player->bIsInteracting = false;	
}

void AEspiritaPlayerController::Interact()
{
	if (!IsValid(Player))
		return;

	Player->DoInteraction();
	Player->bIsInteracting = true;
}

void AEspiritaPlayerController::StartRun()
{
	if (!IsValid(Player))
		return;

	Player->TryStartRun();
}

void AEspiritaPlayerController::StopRun()
{
	if (!IsValid(Player))
		return;

	Player->TryStopRun();
}