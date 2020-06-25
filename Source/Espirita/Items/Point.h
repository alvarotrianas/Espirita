// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Espirita/EspiritaInterfaces/Interoperable.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Point.generated.h"

UCLASS()
class ESPIRITA_API APoint : public AActor, public IInteroperable
{
	GENERATED_BODY()
public:
	APoint();

	UPROPERTY(EditAnywhere)
		float points;
protected:
	virtual void BeginPlay() override;
private:
	class AEspiritaGameModeBase* gameMode;
	void SpawnedPoint();
	void DoPlayerInteraction() override;
};
