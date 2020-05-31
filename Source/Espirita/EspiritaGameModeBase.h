// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EspiritaGameModeBase.generated.h"

/**
 * 
 */
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
	//*current game state*//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int actualGameState;
	//*tick function called every frame *//
	//virtual void Tick(float DeltaTime) override;	
	//*Update the general Score*//
	void UpdateScore(float points);
	//*If a point is spawned in the lvl update points variable*//
	void UpdatePoints(int state);
	//* Get the current points in level *//
	int GetPointsInLevel();
	//*set the key value*//
	void SetRecolectedKeys(int arg);
	int GetRecolectedKeys();

protected:
	virtual void BeginPlay() override;

private:
	//*the points in level*//
	int pointsInLevel;
	//*The game score *//
	float score;
	//*the keys in level every key can open every door*//
	int keys;
};
