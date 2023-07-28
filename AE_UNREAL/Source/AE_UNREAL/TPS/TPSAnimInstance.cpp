// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSAnimInstance.h"
#include "TPSCharacter.h"

void UTPSAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// ���ڽ��� �ִ��ν��Ͻ��Դϴ�.
	// OnMontageEnded.AddDynamic(this, &UTPSAnimInstance::MontageEnd);

	// ���̵�       => ����
	// �귣�� �ƿ�     ������

	OnMontageBlendingOut.AddDynamic(this, &UTPSAnimInstance::MontageEnd);

	// ���� ���� ���͸� ���⼭ �����ɴϴ�.
	// TPSĳ���Ϳ��� �� ������ �����.

	ATPSCharacter* Chracter = Cast<ATPSCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AllAnimations = Chracter->AllAnimations;
}

// �����Ҷ� �ѹ� ������Ʈ�� �����ֹǷ�.
void UTPSAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);

	if (0 == AllAnimations.Num())
	{
		return;
	}

	ATPSCharacter* Chracter = Cast<ATPSCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	AniState = Chracter->AniState;

	class UAnimMontage* Montage = AllAnimations[AniState];

	if (nullptr == Montage)
	{
		return;
	}

	if (false == Montage_IsPlaying(Montage))
	{
		Montage_Play(Montage, 1.0f);
	}
}

void UTPSAnimInstance::MontageEnd(UAnimMontage* Anim, bool _Inter)
{
	TSubclassOf<UAnimInstance> Inst = UTPSAnimInstance::StaticClass();

	ATPSCharacter* Chracter = Cast<ATPSCharacter>(GetOwningActor());

	if (nullptr == Chracter && false == Chracter->IsValidLowLevel())
	{
		return;
	}

	// Anim ����� ��Ÿ��
	if (AllAnimations[TPSAniState::Attack] == Anim)
	{
		AniState = TPSAniState::Idle;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
	}

	if (AllAnimations[TPSAniState::Jump] == Anim)
	{
		AniState = TPSAniState::Idle;
		Chracter->AniState = AniState;
		Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
	}

}
