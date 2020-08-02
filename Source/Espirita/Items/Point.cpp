
#include "Point.h"
#include "Engine/World.h"
#include "Espirita/EspiritaGameModeBase.h"
#include "Espirita/EspiritaInterfaces/Interoperable.h"

void APoint::BeginPlay()
{
	Super::BeginPlay();
	gameMode = GetWorld()->GetAuthGameMode<AEspiritaGameModeBase>();
	gameMode->RegisterSoul(this);
}

void APoint::DoPlayerInteraction()
{
	if (gameMode->TryPickupSoul(this))
	{
		Picked();
		this->Destroy();
	}
}
