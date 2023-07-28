// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_DEATH.h"
#include "AI/Monster.h"
#include "AI/AICon.h"

// 1. 몬스터 죽는 애니메이션을 끝나면 화면에서 완전히 사라져야 합니다.

UBTTask_DEATH::UBTTask_DEATH()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_DEATH::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 현재 AI 컨트롤러를 얻어옴
	AAIController* AIController = OwnerComp.GetAIOwner();

	// AI 컨트롤러가 유효한지 확인
	if (AIController)
	{
		// AI 컨트롤러의 Pawn, 즉 몬스터 액터를 얻어옴
		AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

		// 몬스터 액터가 유효한지 확인하고 setoverlap 함수를 호출
		if (Monster)
		{
			Monster->setoverlap(false);
			// monste->setoverlap(false);
			isDeath = false;
		}
	}
	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::DEATH);

	return EBTNodeResult::Type::InProgress;
}
void UBTTask_DEATH::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DelataSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DelataSeconds);

	UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(UBTTask_AIBase::GetAiState(OwnerComp));
	float Time = Montage->CalculateSequenceLength();

	if (Time <= GetStateTime(OwnerComp))
	{
		isDeath = true;
	}

	if (isDeath == true)
	{
		GetGlobalCharacter(OwnerComp)->Destroy();
	}
}

