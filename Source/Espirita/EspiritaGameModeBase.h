// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Espirita/Items/Point.h"
#include "EspiritaGameModeBase.generated.h"

UCLASS()
class ESPIRITA_API AEspiritaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AEspiritaGameModeBase();
	//*current camera angle*//
	float angle;
	//*current camera distance to player*//
	float distance;
	//*current game state.*//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ActualGameState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float SoulEnergyRecoverRatio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float EnergyRecoveryCooldown;

	//*set the key value*//
	void SetRecolectedKeys(int arg);
	int GetRecolectedKeys();
	
	//Register a soul to be collected during the match.
	void RegisterSoul(APoint* soul);
	//Validate if soul has been registered and returns if the pickup has succeded.
	bool TryPickupSoul(APoint* soul);
	//Spends a certain amount of energy and returns if spend has succeeded
	bool TrySpendEnergy(float amount);
	//Returns the current energy
	float GetCurrentEnergy();
	//Returns the count of all souls in scene
	int GetRegisteredSoulsCount();
	//Returns the count of picked souls in scene
	int GetCurrentSoulsCount();
protected:
	virtual void BeginPlay() override;
private:
	//Id array of registered souls on this match.
	TArray<uint32> registeredSouls;
	//Id array of picked souls on this match.
	TArray<uint32> pickedSouls;
	//Current energy provided by picked souls.
	float currentEnergy;
	//Pick a soul after validation
	void PickupSoul(uint32 id);

	//*the keys in level every key can open every door*//
	int keys;

	//Recover energy based on recover ratio
	UFUNCTION()
		void RecoverEnergy();
	UFUNCTION()
		void EndEnergyCooldown();
};
