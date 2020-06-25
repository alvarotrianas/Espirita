// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interoperable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteroperable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ESPIRITA_API IInteroperable
{
	GENERATED_BODY()
public:
	virtual void DoPlayerInteraction() = 0;
};
