// Fill out your copyright notice in the Description page of Project Settings
#include "StandardEnemy.h"
#include "Engine/TargetPoint.h"

// Sets default values
AStandardEnemy::AStandardEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	ViewColor = FLinearColor(0.661458, 0.0, 0.172445, 1.0);
	DistanceToTarget = INFINITY;
	bIsChasing = false;
}

// Called when the game starts or when spawned
void AStandardEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStandardEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<class ATargetPoint*> AStandardEnemy::GetWayPoints()
{
	return WayPoints;
}

