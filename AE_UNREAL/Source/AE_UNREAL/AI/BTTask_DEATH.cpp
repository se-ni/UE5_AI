// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_DEATH.h"
#include "AI/Monster.h"
#include "AI/AICon.h"

// 1. ���� �״� �ִϸ��̼��� ������ ȭ�鿡�� ������ ������� �մϴ�.

UBTTask_DEATH::UBTTask_DEATH()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}


EBTNodeResult::Type UBTTask_DEATH::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// ���� AI ��Ʈ�ѷ��� ����
	AAIController* AIController = OwnerComp.GetAIOwner();

	// AI ��Ʈ�ѷ��� ��ȿ���� Ȯ��
	if (AIController)
	{
		// AI ��Ʈ�ѷ��� Pawn, �� ���� ���͸� ����
		AMonster* Monster = Cast<AMonster>(AIController->GetPawn());

		// ���� ���Ͱ� ��ȿ���� Ȯ���ϰ� setoverlap �Լ��� ȣ��
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

