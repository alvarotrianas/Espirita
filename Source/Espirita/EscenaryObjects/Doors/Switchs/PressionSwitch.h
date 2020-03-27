// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PressionSwitch.generated.h"

UCLASS()
class ESPIRITA_API APressionSwitch : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APressionSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void OnOverlap(AActor* me, AActor* other);

	UFUNCTION()
		void EndOverlap(AActor* me, AActor* other);

	UPROPERTY(Editanywhere)
		class ADoorWithSwitch* myDoor;
};
