
#include "Point.h"
#include "Engine/World.h"
#include "Espirita/EspiritaGameModeBase.h"
#include "Espirita/EspiritaInterfaces/Interoperable.h"

#define SPAWNED 1
#define TAKEN -1

APoint::APoint()
{
	points = 10.0f;
}

void APoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnedPoint();
}

void APoint::SpawnedPoint() 
{
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	gameMode->UpdatePoints(SPAWNED);
}

void APoint::DoPlayerInteraction()
{
	gameMode->UpdateScore(points);
	gameMode->UpdatePoints(TAKEN);
	this->Destroy();
}
