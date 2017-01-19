// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PatrollingComponent.generated.h"

/**
* A route card to help AI choose their next waypoint
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class S05_TESTINGGROUNDS_API UPatrollingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<AActor*> GetPatrolPoints() const;

private:	

	UPROPERTY(EditInstanceOnly, Category = "Patrol Points")
	TArray<AActor*> PatrolPoints;
	
};
