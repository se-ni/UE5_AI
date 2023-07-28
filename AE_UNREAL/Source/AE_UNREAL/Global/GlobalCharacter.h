// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Global/GlobalAnimInstance.h>
#include "GlobalCharacter.generated.h"

UCLASS()
class AE_UNREAL_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGlobalCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FVector OriginAIPos;

	int GetAniState()
	{
		return AniState;
	}

	template<typename EnumType>
	EnumType GetAniState()
	{
		return static_cast<EnumType>(AniState);
	}

	template<typename EnumType>
	void SetAniState(EnumType _AniState)
	{
		AniState = static_cast<int>(_AniState);
	}

	void SetAniState(int _AniState)
	{
		AniState = _AniState;
	}

	class UGlobalAnimInstance* GetGlobalAnimInstance()
	{
		return GlobalAnimInstance;
	}

	template<typename EnumType>
	class UAnimMontage* GetAnimMontage(EnumType _Index)
	{
		return GetAnimMontage(static_cast<int>(_Index));
	}

	class UAnimMontage* GetAnimMontage(int _Index)
	{
		if (false == AllAnimations.Contains(_Index))
		{
			return nullptr;
		}

		return AllAnimations[_Index];
	}

	template<typename EnumType>
	void SetAllAnimation(const TMap<EnumType, class UAnimMontage*>& _MapAnimation) 
	{
		for (TPair<EnumType, UAnimMontage*> Pair : _MapAnimation)
		{
			AllAnimations.Add(static_cast<int>(Pair.Key), Pair.Value);
		}
	}


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
		float BaseLookUpRate;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	template<typename EnumType>
	void PushAnimation(EnumType _Index, class UAnimMontage* _Montage)
	{
		PushAnimation(static_cast<int>(_Index), _Montage);
	}

	void PushAnimation(int _Index, class UAnimMontage* _Montage)
	{
		if (true == AllAnimations.Contains(_Index))
		{
			return;
		}

		AllAnimations.Add(_Index, _Montage);
	}

private:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int AniState = 0;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, class UAnimMontage*> AllAnimations;


	class UGlobalAnimInstance* GlobalAnimInstance = nullptr;

};
