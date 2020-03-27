// Fill out your copyright notice in the Description page of Project Settings.


#include "PressionSwitch.h"
#include "Espirita/EscenaryObjects/Doors/DoorWithSwitch.h"
#define OFF 1
#define ON -1
// Sets default values
APressionSwitch::APressionSwitch()
{

}


void APressionSwitch::BeginPlay()
{
	Super::BeginPlay();
	if (myDoor != nullptr) {
		myDoor->setnumSwitch(OFF);
	}
	else
	{
		this->Destroy();
	}

	OnActorBeginOverlap.AddDynamic(this, &APressionSwitch::OnOverlap);
	OnActorEndOverlap.AddDynamic(this, &APressionSwitch::EndOverlap);
}

void APressionSwitch::OnOverlap(AActor* me, AActor* other)
{
	if (myDoor != nullptr) {
		myDoor->setActiveSwitch(ON);
	}
}

void APressionSwitch::EndOverlap(AActor* me, AActor* other)
{
	myDoor->setActiveSwitch(OFF);
}

