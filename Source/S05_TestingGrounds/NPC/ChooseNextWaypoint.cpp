// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrollingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get patrolling component
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrollingComp = ControlledPawn->FindComponentByClass<UPatrollingComponent>();
	if (!ensure(PatrollingComp)) 
	{ 
		return EBTNodeResult::Failed; 
	}
	
	//Get patrol points
	auto PatrolPoints = PatrollingComp->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("A Guard is missing patrol points!"));
		return EBTNodeResult::Failed;
	}

	//Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle Index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;
}


