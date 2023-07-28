// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GlobalAnimInstance.generated.h"



/**
 * 
 */
UCLASS()
class AE_UNREAL_API UGlobalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
	int AniState = 0;

	int DefaultAniState = -1;

	TMap<int, class UAnimMontage*> AllAnimations;

	class UAnimMontage* CurMontage = nullptr;

	UFUNCTION()
	void MontageEnd(UAnimMontage* Anim, bool _Inter);

	template<typename EnumType>
	void SetDefaultAniState(EnumType _DefaultState)
	{
		DefaultAniState = static_cast<int>(_DefaultState);
	}

	void SetDefaultAniState(int _DefaultState)
	{
		DefaultAniState = _DefaultState;
	}

	// �ִ��ν��Ͽ� Tick�� BeginPlay

protected:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float _DeltaTime) override;
};
