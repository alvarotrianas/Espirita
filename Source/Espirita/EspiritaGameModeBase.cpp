// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "EspiritaGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Espirita/Core/EspiritaPlayerController.h"
 


#define PLAYING 0
#define WIN 1
#define LOSE -1


AEspiritaGameModeBase::AEspiritaGameModeBase()
{
	//set tick enble
	//PrimaryActorTick.bCanEverTick = true;

	angle = 0;
	distance = 0;

	pointsInLevel = 0;
	score = 0.f;
	keys = 0;

	actualGameState = PLAYING;
	
	PlayerControllerClass = AEspiritaPlayerController::StaticClass();
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Espirita/BP_Espirita"));

	if (PlayerPawnBPClass.Class != NULL)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}

void AEspiritaGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
/* tick function
void AMyProjectGameMode::Tick(float DeltaTime)
{

}*/

void AEspiritaGameModeBase::UpdateScore(float points) {
	score += points;
	UE_LOG(LogTemp, Warning, TEXT("%f \n"), score);
}

void AEspiritaGameModeBase::UpdatePoints(int state) {
	pointsInLevel += state;
	if (pointsInLevel <= 0)
	{
		actualGameState = WIN;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	//UE_LOG(LogTemp, Warning, TEXT("%d \n"), pointsInLevel);
}

int AEspiritaGameModeBase::GetPointsInLevel()
{
	return pointsInLevel;
}

void AEspiritaGameModeBase::SetRecolectedKeys(int arg)
{
	keys += arg;
}

int AEspiritaGameModeBase::GetRecolectedKeys()
{
	return keys;
}
