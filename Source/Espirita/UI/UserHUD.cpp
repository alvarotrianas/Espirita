// Fill out your copyright notice in the Description page of Project Settings.
#include "UserHUD.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"
#include "Espirita/EspiritaGameModeBase.h"

int lastGameMode = -1;
int lastPoints = -1;
int currentPoints = -1;

void UUserHUD::NativeConstruct()
{
	Super::NativeConstruct();
	AGameModeBase* mode = GetWorld()->GetAuthGameMode();

	if (mode != nullptr)
		gameMode = Cast<AEspiritaGameModeBase>(mode);
	else
		UE_LOG(LogTemp, Warning, TEXT("No game Mode \n"));

	totalPoints = gameMode->GetPointsInLevel();
	currentPoints = totalPoints - gameMode->GetPointsInLevel();
}

void UUserHUD::NativeTick(const FGeometry& geometry, float InDeltaTime)
{
	Super::NativeTick(geometry, InDeltaTime);

	ListenGameModeChanges();
	ListenPointsChanges();
}

void UUserHUD::ListenGameModeChanges(void)
{
	if (gameMode->actualGameState != lastGameMode)
	{
		GameModeUpdated(gameMode->actualGameState);
		lastGameMode = gameMode->actualGameState;
	}
}

void UUserHUD::ListenPointsChanges(void)
{
	currentPoints = totalPoints - gameMode->GetPointsInLevel();

	if (currentPoints != lastPoints)
	{
		PointsUpdated(currentPoints);
		lastPoints = currentPoints;
	}
}
