// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Espirita/EspiritaInterfaces/Interoperable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NormalKey.generated.h"

UCLASS()
class ESPIRITA_API ANormalKey : public AActor, public IInteroperable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANormalKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	class AEspiritaGameModeBase* gameMode;

public:
	//interaction with player
	void DoPlayerInteraction() override;
};
