// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MathWidget.generated.h"

/**
 * 
 */
UCLASS()
class AE_UNREAL_API UMathWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FString CPText;

	int Value = 0;

	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// �ٸ� ���͵��� �ʿ��Ҷ�����
	// �̳༮�� �ƴ°� ����
	// 100����
	// AMathGameMode* Mode;
	// APlayer*
};
