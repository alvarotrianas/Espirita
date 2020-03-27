// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalKey.h"

#include "Engine/World.h"
#include "Espirita/EspiritaGameModeBase.h"


#define TAKEN 1
// Sets default values
ANormalKey::ANormalKey()
{
}

// Called when the game starts or when spawned
void ANormalKey::BeginPlay()
{
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	Super::BeginPlay();

}


void ANormalKey::DoPlayerInteraction()
{
	gameMode->SetRecolectedKeys(TAKEN);
	this->Destroy();
}
