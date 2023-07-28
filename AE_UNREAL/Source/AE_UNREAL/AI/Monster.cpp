// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Monster.h"
#include <Global/GlobalGameInstance.h>
#include <Global/Data/MonsterData.h>
#include "Components/CapsuleComponent.h"
#include "AI/BTTask_DEATH.h"
#include "BehaviorTree/BlackboardComponent.h"


void AMonster::BeginPlay()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::BeginOverLap);

	UGlobalGameInstance* Inst = GetWorld()->GetGameInstance<UGlobalGameInstance>();

	if (nullptr != Inst)
	{
		CurMonsterData = Inst->GetMonsterData(DataName);

		SetAllAnimation(CurMonsterData->MapAnimation);
		SetAniState(AIState::DEATH);
	}

	Super::BeginPlay();

	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), static_cast<uint8>(AIState::IDLE));
	GetBlackboardComponent()->SetValueAsString(TEXT("TargetTag"), TEXT("Player"));
	GetBlackboardComponent()->SetValueAsFloat(TEXT("SearchRange"), 1000.0f);
	GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), 200.0f);

	// GetBlackboardComponent()->SetValueAsFloat(TEXT("ReturnRange"), 200.0f);
}

void AMonster::BeginOverLap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor->ActorHasTag(TEXT("PlayerAttack")))
	{
		UE_LOG(LogTemp, Log, TEXT("%S(%u) Overlapped"), __FUNCTION__, __LINE__);
		isoverlap = true;
	//	UBTTask_DEATH* TaskDeath = NewObject<UBTTask_DEATH>();
	//	// 인스턴스를 사용하여 GetDeath 함수 호출
	//	bool bIsDeath = TaskDeath->GetDeath();
	//	if (bIsDeath == true)
	//	{
	//		
	//	}	
	}
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isoverlap)
	{
		GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), static_cast<uint8>(AIState::DEATH));
	}
}