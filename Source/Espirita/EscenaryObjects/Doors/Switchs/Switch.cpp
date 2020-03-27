// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
#include "Espirita/EscenaryObjects/Doors/DoorWithSwitch.h"

#define OFF 1
#define ON -1

ASwitch::ASwitch()
{

}


void ASwitch::BeginPlay()
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

void ASwitch::OnOverlap(AActor* me, AActor* other)
{
	if (myDoor != nullptr) {
		myDoor->setActiveSwitch(ON);
	}
}