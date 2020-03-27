// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Espirita/EscenaryObjects/Doors/Door.h"
#include "DoorWithKey.generated.h"

/**
 * 
 */
UCLASS()
class ESPIRITA_API ADoorWithKey : public ADoor
{
	GENERATED_BODY()

		void DoPlayerInteraction() override;
};
