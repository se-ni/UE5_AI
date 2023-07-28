#pragma once

#include "CoreMinimal.h"
#include "BTTask_AIBase.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_RETURN.generated.h"

/**
 *
 */
UCLASS()
class AE_UNREAL_API UBTTask_RETURN : public UBTTask_AIBase
{
	GENERATED_BODY()

		UBTTask_RETURN();


	FVector OriginAIPos;
	bool bReturning = false;


protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DelataSeconds);
};