// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "EspiritaGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Espirita/Core/EspiritaPlayerController.h"
#include "Espirita/Items/Point.h"

#define PLAYING 0
#define WIN 1
#define LOSE -1
#define BASE_SOULS 0

FTimerHandle EnergyRecoverTimerHandle;
FTimerHandle EnergyRecoverCooldown;
bool isEnergyInCoolDown;

AEspiritaGameModeBase::AEspiritaGameModeBase()
{
	angle = 0;
	distance = 0;

	SoulEnergyRecoverRatio = 0.1F;
	currentEnergy = BASE_SOULS;
	keys = 0;

	ActualGameState = PLAYING;
	PlayerControllerClass = AEspiritaPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Espirita/BP_Espirita"));

	if (PlayerPawnBPClass.Class != NULL)
		DefaultPawnClass = PlayerPawnBPClass.Class;
}

void AEspiritaGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(EnergyRecoverTimerHandle, this, &AEspiritaGameModeBase::RecoverEnergy, 0.1F, true, 0.0f);
}

void AEspiritaGameModeBase::RecoverEnergy()
{
	if (!isEnergyInCoolDown)
	{
		if (currentEnergy < (pickedSouls.Num() + BASE_SOULS))
			currentEnergy += SoulEnergyRecoverRatio;

		if (currentEnergy > (pickedSouls.Num() + BASE_SOULS))
			currentEnergy = (pickedSouls.Num() + BASE_SOULS);
	}
}

void AEspiritaGameModeBase::RegisterSoul(APoint* soul)
{
	if (!registeredSouls.Contains(soul->GetUniqueID()))
		registeredSouls.Add(soul->GetUniqueID());
}

bool AEspiritaGameModeBase::TryPickupSoul(APoint* soul)
{
	uint32 id = soul->GetUniqueID();
	bool isRegistered = registeredSouls.Contains(id);
	bool isPicked = pickedSouls.Contains(id);
	bool isValid = isRegistered && !isPicked;

	if (isValid)
		PickupSoul(id);
	else
		UE_LOG(LogTemp, Error, TEXT("Trying pick an unregistered or already picked soul."));

	return isValid;
}

void AEspiritaGameModeBase::PickupSoul(uint32 id)
{
	pickedSouls.Add(id);
	GetWorld()->GetTimerManager().ClearTimer(EnergyRecoverCooldown);
	isEnergyInCoolDown = false;

	if (pickedSouls.Num() == registeredSouls.Num())
	{
		ActualGameState = WIN;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

bool AEspiritaGameModeBase::TrySpendEnergy(float amount)
{
	if (amount >= 0 && currentEnergy >= amount)
	{
		isEnergyInCoolDown = true;
		GetWorld()->GetTimerManager().SetTimer(EnergyRecoverCooldown, this, &AEspiritaGameModeBase::EndEnergyCooldown, EnergyRecoveryCooldown, false, EnergyRecoveryCooldown);
		currentEnergy -= amount;
		return true;
	}

	return false;
}

void AEspiritaGameModeBase::EndEnergyCooldown()
{
	isEnergyInCoolDown = false;
	GetWorld()->GetTimerManager().ClearTimer(EnergyRecoverCooldown);
}

float AEspiritaGameModeBase::GetCurrentEnergy()
{
	return currentEnergy;
}

int AEspiritaGameModeBase::GetRegisteredSoulsCount()
{
	return registeredSouls.Num();
}

int AEspiritaGameModeBase::GetCurrentSoulsCount()
{
	return pickedSouls.Num();
}

void AEspiritaGameModeBase::SetRecolectedKeys(int arg)
{
	keys += arg;
}

int AEspiritaGameModeBase::GetRecolectedKeys()
{
	return keys;
}
