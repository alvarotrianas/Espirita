// Fill out your copyright notice in the Description page of Project Settings.


#include "UserHUD.h"

#include "Engine/World.h"
#include "Components/TextBlock.h"
#include "Espirita/EspiritaGameModeBase.h"

#define PLAYING 0
#define WIN 1
#define LOSE -1

void UUserHUD::NativeTick(const FGeometry& geometry, float InDeltaTime)
{
	Super::NativeTick(geometry, InDeltaTime);
	//set the text bloc games
	UpdatePoints();
	SetFinalText();
}

//*convert a float type into a FText type for UI*//
FText UUserHUD::FloatToText(float parameter)
{
	FString parameterString = FString::SanitizeFloat(parameter);
	FText parameterText = FText::FromString(parameterString);
	return parameterText;
}
//*convert a int type into a FText type for UI*//
FText UUserHUD::IntToText(int parameter)
{
	FString parameterString = FString::FromInt(parameter);
	FText parameterText = FText::FromString(parameterString);
	return parameterText;
}

//set the final text on the screen
void UUserHUD::SetFinalText()
{
	if (gameMode->actualGameState != PLAYING) {
		//UpdatePoints();
		if (gameMode->actualGameState == WIN) {
			EndGame->SetText(FText::FromString("WIN"));
		}
		else {
			EndGame->SetText(FText::FromString("LOSE"));
		}
		Restart->SetText(FText::FromString("PRESS SPACE BAR FOR RESTART"));
	}
}

void UUserHUD::UpdatePoints()
{
	currentPoints = totalPoints - gameMode->GetPointsInLevel();
	//handle new points or thread points errors
	if (currentPoints < 0) {
		totalPoints = gameMode->GetPointsInLevel();
		TotalItemsTest->SetText(IntToText(totalPoints));
		pointsRemain = totalPoints - gameMode->GetPointsInLevel();
		ItemsRemain->SetText(IntToText(pointsRemain));
	}
	if (currentPoints - pointsRemain != 0) {
		pointsRemain = currentPoints;
		ItemsRemain->SetText(IntToText(pointsRemain));
	}
}

void UUserHUD::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("HOLA \n"));
	//Get the game mode an verify if exist
	AGameModeBase* mode = GetWorld()->GetAuthGameMode();
	if (mode != nullptr) {
		gameMode = Cast<AEspiritaGameModeBase>(mode);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No game Mode \n"));
	}
	//set total points
	totalPoints = gameMode->GetPointsInLevel();
	TotalItemsTest->SetText(IntToText(totalPoints));
	pointsRemain = totalPoints - gameMode->GetPointsInLevel();
	ItemsRemain->SetText(IntToText(pointsRemain));
}
