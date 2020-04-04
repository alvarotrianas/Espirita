// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_CheckDistance.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMyBTService_CheckDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	

	UObject *TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsClass(bbTarget.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(TargetObject);

	if (IsValid(TargetActor))
	{
		FVector OwnerLocation = OwnerComp.GetOwner()->GetActorLocation();
		FVector TargetLocation = TargetActor->GetActorLocation();
		TargetLocation =   (OwnerLocation - TargetLocation) * FVector(1.0f, 1.0f, 0.0f);

		float Diff = TargetLocation.Size();
		if (Diff < MinDistance)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(bbCheck.SelectedKeyName,true);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(bbCheck.SelectedKeyName, false);
		}
	}
}