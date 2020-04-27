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
	OnActorBeginOverlap.AddDynamic(this, &ASwitch::OnOverlap);

	if (myDoor != nullptr) 
	{
		myDoor->setnumSwitch(OFF);
	}
	else
	{
		this->Destroy();
	}
	
}

void ASwitch::OnOverlap(AActor* me, AActor* other)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));

	if (myDoor != nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
		myDoor->setActiveSwitch(ON);
	}
}