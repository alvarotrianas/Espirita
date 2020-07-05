// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevelDoor.h"
#include "Espirita/EspiritaGameModeBase.h"

void AEndLevelDoor::DoPlayerInteraction()
{
	if (gameMode->TryEndLevel())
		EndLevelSucceeded();
	else
		EndLevelFailed();
}