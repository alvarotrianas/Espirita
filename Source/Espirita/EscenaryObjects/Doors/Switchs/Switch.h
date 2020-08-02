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
	virtual void BeginPlay() override;
public:	
	ASwitch();

	UFUNCTION()
		void OnOverlap(AActor* me, AActor* other);

	UPROPERTY(EditAnywhere)
		class ADoorWithSwitch* myDoor;
};
