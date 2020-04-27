// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorWithSwitch.h"

ADoorWithSwitch::ADoorWithSwitch()
{
	numSwitch = 0;
}

void ADoorWithSwitch::setnumSwitch(int arg)
{
	numSwitch += arg;
}

void ADoorWithSwitch::setActiveSwitch(int arg)
{
	numSwitch += arg;
	if (numSwitch <= 0) 
	{
		bIsActive = true;
	}
	else
	{
		bIsActive = false;
	}
}
//do nothing at this moment
void ADoorWithSwitch::DoPlayerInteraction()
{
	UE_LOG(LogTemp, Warning, TEXT("I have to react %d"), numSwitch);
}
