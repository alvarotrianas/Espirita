// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_GoToNextPatrollPoint.generated.h"

struct FNextWaypoint
{
    int CurrentIndex = -1;
};

/**
 * 
 */
UCLASS()
class ESPIRITA_API UBTTask_GoToNextPatrollPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere) FBlackboardKeySelector bbTargetWayPoint;

    uint16 GetInstanceMemorySize() const override;

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp,uint8* NodeMemory) override;
};
