// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorWithKey.h"
#include "Engine/World.h"
#include "Espirita/EspiritaGameModeBase.h"

void ADoorWithKey::DoPlayerInteraction()
{
	int currentPlayerKeys = gameMode->GetRecolectedKeys();
	if (currentPlayerKeys > 0) {
		bIsActive = true;
		//UE_LOG(LogTemp, Warning, TEXT("Opening A Door that have a key %d \n"), currentPlayerKeys);
	}

}