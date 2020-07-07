// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Switch.generated.h"

UCLASS()
class ESPIRITA_API ASwitch : public APawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void OnOverlap(AActor* me, AActor* other);

	UPROPERTY(Editanywhere)
		class ADoorWithSwitch* myDoor;
};
