// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GoToNextPatrollPoint.h"
#include "AIController.h"
#include "Espirita/EspiritaInterfaces/PatrollObject.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"

uint16 UBTTask_GoToNextPatrollPoint::GetInstanceMemorySize() const
{
	return sizeof(FNextWaypoint);
}

EBTNodeResult::Type UBTTask_GoToNextPatrollPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* CurrentController = Cast<AAIController>(OwnerComp.GetOwner());
	if(!IsValid(CurrentController)) return EBTNodeResult::Failed;
    IPatrollObject *PatrollPawn =	Cast<IPatrollObject>(CurrentController->GetPawn());
	if (!(PatrollPawn)) return EBTNodeResult::Failed;
	
	TArray<ATargetPoint*> Waypoints =  PatrollPawn->GetWayPoints();
	if (Waypoints.Num() == 0)
	{
		return EBTNodeResult::Aborted;
	}
	FNextWaypoint* Data = (FNextWaypoint*)NodeMemory;

	Data->CurrentIndex++;

	if (Data->CurrentIndex < 0 || Data->CurrentIndex >= Waypoints.Num())
	{
		Data->CurrentIndex = 0;
	}
	ATargetPoint* CurrentWayPoint = Waypoints[Data->CurrentIndex];
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();

	BlackBoard->SetValueAsVector(bbTargetWayPoint.SelectedKeyName, CurrentWayPoint->GetActorLocation());

	return EBTNodeResult::Succeeded;
}