// Fill out your copyright notice in the Description page of Project Settings.
#include "UserHUD.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"
#include "Espirita/EspiritaGameModeBase.h"

int lastGameMode = -1;
int lastPoints = -1;

void UUserHUD::NativeConstruct()
{
	Super::NativeConstruct();
	AGameModeBase* mode = GetWorld()->GetAuthGameMode();

	if (mode != nullptr)
		gameMode = Cast<AEspiritaGameModeBase>(mode);
	else
		UE_LOG(LogTemp, Warning, TEXT("No game Mode \n"));

	totalSouls = gameMode->GetRegisteredSoulsCount();
	currentSouls = totalSouls - gameMode->GetCurrentSoulsCount(); 
	lastGameMode = -1;
	lastPoints = -1;
}

void UUserHUD::NativeTick(const FGeometry& geometry, float InDeltaTime)
{
	Super::NativeTick(geometry, InDeltaTime);

	ListenGameModeChanges();
	ListenPointsChanges();
	currentEnergy = gameMode->GetCurrentEnergy();
	currentEnergyPct = gameMode->GetCurrentEnergy() / totalSouls;
}

void UUserHUD::ListenGameModeChanges(void)
{
	if (gameMode->ActualGameState != lastGameMode)
	{
		GameModeUpdated(gameMode->ActualGameState);
		lastGameMode = gameMode->ActualGameState;
	}
}

void UUserHUD::ListenPointsChanges(void)
{
	currentSouls = gameMode->GetCurrentSoulsCount();

	if (currentSouls != lastPoints)
	{
		PointsUpdated(currentSouls);
		lastPoints = currentSouls;
	}
}
