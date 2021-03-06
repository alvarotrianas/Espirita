// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Espirita/EscenaryObjects/Doors/Door.h"
#include "DoorWithSwitch.generated.h"

/**
 * 
 */
UCLASS()
class ESPIRITA_API ADoorWithSwitch : public ADoor
{
	GENERATED_BODY()
private:
	int numSwitch;
protected:
	void BeginPlay() override;
public:
	ADoorWithSwitch();

	UPROPERTY(EditAnywhere)
		bool StartActive;
	UPROPERTY(Editanywhere)
		bool isInverted;

	void setnumSwitch(int arg);
	void setActiveSwitch(int arg);
	//to implement future interact with swicht doors
	void DoPlayerInteraction() override;
	
};
