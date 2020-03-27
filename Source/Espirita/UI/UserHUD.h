// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserHUD.generated.h"

/**
 * 
 */
UCLASS()
class ESPIRITA_API UUserHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	//*Natve functions of UI*//
	void NativeConstruct() override;
	void NativeTick(const FGeometry& geometry, float InDeltaTime) override;

private:
	//*Game mode pointer*//
	class AEspiritaGameModeBase* gameMode;
	//*UI Elements*//
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* EndGame;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Restart;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* ItemsRemain;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TotalItemsTest;
	//UPROPERTY(meta = (BindWidget))
	//class UTextBlock* PickWait;
	//* variables *//
	int totalPoints;
	int currentPoints;
	int pointsRemain;
	//*Update UI functions*//
	FText FloatToText(float angle);
	FText IntToText(int arg);
	void SetFinalText();
	void UpdatePoints();
};
