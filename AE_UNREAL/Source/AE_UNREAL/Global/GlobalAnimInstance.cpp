// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalAnimInstance.h"
#include "GlobalCharacter.h"
#include <Global/Data/MonsterData.h>
#include "ARGlobal.h"

void UGlobalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OnMontageBlendingOut.AddDynamic(this, &UGlobalAnimInstance::MontageEnd);
}

// �����Ҷ� �ѹ� ������Ʈ�� �����ֹǷ�.
void UGlobalAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	AGlobalCharacter* Chracter = Cast<AGlobalCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->GetAniState();

	class UAnimMontage* Montage = AllAnimations[AniState];

	if (nullptr == Montage)
	{
		return;
	}

	// ����1. ��Ÿ�� ����� ������.
	// ����2. ������ �̹� ����� ��Ÿ�ִ�.
	// ����3. ��Ÿ�ְ� ������.
	if (false == Montage_IsPlaying(Montage))
	{
		//if (Montage == CurMontage && -1 != DefaultAniState && false == Montage->bLoop)
		//{
		//	Montage = AllAnimations[DefaultAniState];
		//}

		CurMontage = Montage;
		Montage_Play(Montage, 1.0f);
	}
}

void UGlobalAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{

}
