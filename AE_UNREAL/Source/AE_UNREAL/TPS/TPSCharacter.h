// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSEnums.h"
#include "TPSCharacter.generated.h"

// ��� ��� ���� �Ʒ��� �־�� �մϴ�.

UCLASS()
class AE_UNREAL_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacter();

	// �������Ʈ���� ȣ���ϰ� �Ϸ��� �⺻������ public�̾�� �մϴ�.
	UFUNCTION(BlueprintCallable)
	void AnimationTick();

	// UFUNCTION()
	// void MontageEnd(UAnimMontage* Anim, bool _Inter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame

	// Called to bind functionality to input

	void AttackAction();
	void JumpAction();
	void JumpAxis(float Rate);

	void MoveRight(float Val);
	void MoveForward(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	float BaseLookUpRate;

	bool AxisJump = false;


	// �ִϸ��̼ǿ� �̹� FSM�� ����ϰ� �ִٰ� �ص� ����� ����.
	UPROPERTY(Category = "GameModeValue", EditAnywhere, BlueprintReadWrite)
	TPSAniState AniState = TPSAniState::Idle;

	UPROPERTY(Category = "AnimationValue", EditAnywhere, BlueprintReadWrite)
	TMap<TPSAniState, class UAnimMontage*> AllAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WeaponMesh;

	// �������Ʈ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> WeaponArrays;
};
