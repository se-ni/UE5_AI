// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTTask_AIBase.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_DEATH.generated.h"

/**
 * 
 */
UCLASS()
class AE_UNREAL_API UBTTask_DEATH : public UBTTask_AIBase
{
	GENERATED_BODY()

	UBTTask_DEATH();

	bool isDeath = false;

public:
	bool GetDeath()
	{
		return isDeath;
	}

protected:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds) override;
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
