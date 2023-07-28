#include "AI/BTTask_RETURN.h"
#include "AI/BTTask_PATROL.h"
#include "Global/AICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_RETURN::UBTTask_RETURN()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;

	// OriginAIPos = AAICharacter::GetOriginPos();

}

EBTNodeResult::Type UBTTask_RETURN::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	GetGlobalCharacter(OwnerComp)->SetAniState(AIState::RETURN);



	return EBTNodeResult::InProgress;
}

void UBTTask_RETURN::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// GetGlobalCharacter(OwnerComp)->SetAniState(AIState::MOVE);

	// 기본 위치(OriginAIPos)를 가져옵니다.
	OriginAIPos = GetGlobalCharacter(OwnerComp)->OriginAIPos;

	FVector TargetPos = OriginAIPos;
	FVector ThisPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();
	// 혹시라도 z축이 있을 가능성을 없애는게 보통입니다.
	TargetPos.Z = 0.0f;
	ThisPos.Z = 0.0f;

	FVector Dir = TargetPos - ThisPos;
	Dir.Normalize();
	{
		FVector OtherForward = GetGlobalCharacter(OwnerComp)->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		if (FMath::Abs(Angle0 - Angle1) >= 10.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 500.0f * DeltaSeconds });
			GetGlobalCharacter(OwnerComp)->AddActorWorldRotation(Rot);
		}
		else
		{
			FRotator Rot = Dir.Rotation();
			GetGlobalCharacter(OwnerComp)->SetActorRotation(Rot);
		}
	}

	FVector NowPos = GetGlobalCharacter(OwnerComp)->GetActorLocation();

	Dir = TargetPos - NowPos;

	GetGlobalCharacter(OwnerComp)->AddMovementInput(Dir);

	if (Dir.X < 1.0f)
	{
		bReturning = true;
	}

	//UAnimMontage* Montage = GetGlobalCharacter(OwnerComp)->GetAnimMontage(UBTTask_AIBase::GetAiState(OwnerComp));
	//float Time = Montage->CalculateSequenceLength();

	//if (Time <= GetStateTime(OwnerComp))
	//{
	//	SetStateChange(OwnerComp, AIState::IDLE);
	//	// GetGlobalCharacter(OwnerComp)->SetAniState(AIState::IDLE);
	//	return;
	//}

	if (bReturning)
	{

		GetGlobalCharacter(OwnerComp)->SetAniState(AIState::IDLE);
		SetStateChange(OwnerComp, AIState::IDLE);
		bReturning = false;
	}
}