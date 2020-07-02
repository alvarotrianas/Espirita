// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserHUD.generated.h"

UCLASS()
class ESPIRITA_API UUserHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void NativeTick(const FGeometry& geometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		int currentSouls;
	UPROPERTY(BlueprintReadOnly)
		int totalSouls;
	UPROPERTY(BlueprintReadOnly)
		float currentEnergy;
	UPROPERTY(BlueprintReadOnly)
		float currentEnergyPct;
	UFUNCTION(BlueprintImplementableEvent)
		void GameModeUpdated(int state);
	UFUNCTION(BlueprintImplementableEvent)
		void PointsUpdated(int points);
private:
	class AEspiritaGameModeBase* gameMode;

	void ListenGameModeChanges(void);
	void ListenPointsChanges(void);
};
