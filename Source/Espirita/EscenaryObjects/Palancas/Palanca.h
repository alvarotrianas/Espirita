// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Espirita/EspiritaInterfaces/Interoperable.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Palanca.generated.h"

UCLASS()
class ESPIRITA_API APalanca : public APawn, public IInteroperable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APalanca();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void DoPlayerInteraction() override;

	UPROPERTY(Editanywhere, Category = Switch)
		class ADoorWithSwitch* myDoor;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = Switch)
		bool bIsActive;
};
