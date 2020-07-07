// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorWithSwitch.h"

ADoorWithSwitch::ADoorWithSwitch()
{
	numSwitch = 0;
}

void ADoorWithSwitch::BeginPlay()
{
	Super::BeginPlay();

	if (StartActive)
		setActiveSwitch(-1);
}

void ADoorWithSwitch::setnumSwitch(int arg)
{
	numSwitch += arg;
}

void ADoorWithSwitch::setActiveSwitch(int arg)
{
	numSwitch += arg;

	if (numSwitch <= 0) 
		bIsActive = isInverted ? false : true;
	else
		bIsActive = isInverted ? true : false;
}
//do nothing at this moment
void ADoorWithSwitch::DoPlayerInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("I have to react %d"), numSwitch);
}
