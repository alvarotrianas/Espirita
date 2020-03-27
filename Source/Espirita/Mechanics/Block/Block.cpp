// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABlock::ABlock()
{

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	// ... setup your box component here ...
	RootComponent = BoxComponent;


	normalBlock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Normal Block"));
	normalBlock->SetupAttachment(RootComponent);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> normalBlockAsset(TEXT("/Game/Geometry/Cube_Rock/CubeRock.CubeRock"));


	if (normalBlockAsset.Succeeded())
	{
		normalBlock->SetStaticMesh(normalBlockAsset.Object);
		normalBlock->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		normalBlock->SetWorldScale3D(FVector(1.0f));
	}

}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	
}
