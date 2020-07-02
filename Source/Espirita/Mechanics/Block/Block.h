// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class ESPIRITA_API ABlock : public AActor
{
	GENERATED_BODY()
public:
	ABlock();
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Block")
		UStaticMeshComponent* normalBlock;

	UBoxComponent* BoxComponent;
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnBlock();
	UFUNCTION(BlueprintImplementableEvent)
		void RemoveBlock();
};
