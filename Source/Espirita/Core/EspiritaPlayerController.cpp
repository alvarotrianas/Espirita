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
	//if(IsValid(Player))	UE_LOG(LogTemp, Warning, TEXT("Your message"));
}

void AEspiritaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AEspiritaPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AEspiritaPlayerController::MoveRight);
	
	InputComponent->BindAction("PutBlock", IE_Pressed, this, &AEspiritaPlayerController::PutBlock);
	//InputComponent->BindAction("PutBlock", IE_Released, this, &AEspiritaPlayerController::PutBlock);

	InputComponent->BindAction("PickUp", IE_Pressed, this, &AEspiritaPlayerController::Interact);
	InputComponent->BindAction("PickUp", IE_Released, this, &AEspiritaPlayerController::StopInteract);

	
	
	FInputActionBinding& toggle = InputComponent->BindAction("RestartLevel", IE_Pressed, this, &AEspiritaPlayerController::RestarEspiritatLevel);
	toggle.bExecuteWhenPaused = true;
}


void AEspiritaPlayerController::MoveForward(float Value)
{
	if ((Value != 0.0f) && IsValid(Player))
	{
		// find out which way is forward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		Player->AddMovementInput(Direction, Value);
	}
}

void AEspiritaPlayerController::MoveRight(float Value)
{
	if ((Value != 0.0f) && IsValid(Player))
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		Player->AddMovementInput(Direction, Value);
	}
}

void AEspiritaPlayerController::RestarEspiritatLevel()
{
	AEspiritaGameModeBase * gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	if (gameMode->actualGameState != PLAYING) 
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
		//GetWorld()->ServerTravel(gameMode->GetName());
	}
}

void AEspiritaPlayerController::PutBlock()
{
	if (IsValid(Player) && !Player->bIsCasting)
		Player->InvokeBlock();
}

void AEspiritaPlayerController::StopInteract()
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Interact"));
	/*
	canPick = false;
	timerCalls = 0.0f;
	*/
	if (IsValid(Player)) Player->bIsInteracting = false;
	
}

void AEspiritaPlayerController::Interact()
{
	//UE_LOG(LogTemp, Warning, TEXT("Interact"));
	//canPick = true;
	if (IsValid(Player))
	{
		Player->DoInteraction();
		Player->bIsInteracting = true;
		//Player->InteractObject->DoPlayerInteraction();
	}
}
