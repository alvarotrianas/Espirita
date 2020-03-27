
#include "Point.h"
#include "Engine/World.h"
#include "Espirita/EspiritaGameModeBase.h"
#include "Espirita/EspiritaInterfaces/Interoperable.h"

#define SPAWNED 1
#define TAKEN -1
// Sets default values
APoint::APoint()
{
	points = 10.0f;

}

// Called when the game starts or when spawned
void APoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnedPoint();
}

void APoint::SpawnedPoint() {
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	gameMode->UpdatePoints(SPAWNED);
}

void APoint::DoPlayerInteraction()
{
	gameMode->UpdateScore(points);
	gameMode->UpdatePoints(TAKEN);
	this->Destroy();
}
