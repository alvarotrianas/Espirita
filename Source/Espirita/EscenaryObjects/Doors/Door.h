// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Espirita/EspiritaInterfaces/Interoperable.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Door.generated.h"

UCLASS()
class ESPIRITA_API ADoor : public APawn, public IInteroperable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class AEspiritaGameModeBase* gameMode;

public:
	//interaction with player
	void DoPlayerInteraction() override;

	UPROPERTY(BlueprintReadWrite, Category = MyDoor)
		bool bIsActive;
};
