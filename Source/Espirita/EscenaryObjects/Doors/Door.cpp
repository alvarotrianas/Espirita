// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Engine/World.h"
#include "Espirita/EspiritaGameModeBase.h"

// Sets default values
ADoor::ADoor()
{
	bIsActive = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	Super::BeginPlay();
}

void ADoor::DoPlayerInteraction()
{
	bIsActive = true;
	//UE_LOG(LogTemp, Warning, TEXT("Opening A Door \n"));
}



