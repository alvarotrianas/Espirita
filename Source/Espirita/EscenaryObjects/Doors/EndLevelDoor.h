// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Espirita/EscenaryObjects/Doors/Door.h"
#include "EndLevelDoor.generated.h"

/**
 * 
 */
UCLASS()
class ESPIRITA_API AEndLevelDoor : public ADoor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void EndLevelSucceeded();
	UFUNCTION(BlueprintImplementableEvent)
		void EndLevelFailed();

	void DoPlayerInteraction() override;
};
