// Fill out your copyright notice in the Description page of Project Settings.


#include "Palanca.h"
#include "Espirita/EscenaryObjects/Doors/DoorWithSwitch.h"
#define OFF 1
#define ON -1

// Sets default values
APalanca::APalanca()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void APalanca::BeginPlay()
{
	Super::BeginPlay();
	if (myDoor != nullptr) {
		myDoor->setnumSwitch(OFF);
	}
	else
	{
		this->Destroy();
	}
}

void APalanca::DoPlayerInteraction()
{
	if (myDoor != nullptr) {
		if (bIsActive)
		{
			myDoor->setActiveSwitch(OFF);
		}
		else
		{
			myDoor->setActiveSwitch(ON);
		}
		//this->Destroy();
		bIsActive = !bIsActive;
	}
}
