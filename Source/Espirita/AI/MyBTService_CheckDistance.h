// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class ESPIRITA_API UMyBTService_CheckDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere) float MinDistance;
    UPROPERTY(EditAnywhere) FBlackboardKeySelector bbTarget;
    UPROPERTY(EditAnywhere) FBlackboardKeySelector bbCheck;
protected:
    void TickNode(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory,float DeltaSeconds) override;
};
