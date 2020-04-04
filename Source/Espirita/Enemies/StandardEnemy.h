// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Espirita/EspiritaInterfaces/PatrollObject.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StandardEnemy.generated.h"

UCLASS()
class ESPIRITA_API AStandardEnemy : public ACharacter, public IPatrollObject
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AStandardEnemy();
	UPROPERTY(BlueprintReadWrite, Category = "EstandardEnemy")
		FLinearColor ViewColor;
	UPROPERTY(BlueprintReadWrite, Category = "EstandardEnemy")
		float DistanceToTarget;
	UPROPERTY(BlueprintReadWrite, Category = "EstandardEnemy")
		bool bIsChasing;

	UPROPERTY(EditAnywhere, Category = "EstandardEnemy")
		TArray<class ATargetPoint*> WayPoints;

	virtual TArray<class ATargetPoint*> GetWayPoints() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
};
