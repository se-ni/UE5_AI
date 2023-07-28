// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class AE_UNREAL_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetStatusWindowOnOffSwitch()
	{
		StatusWindowOnOff = StatusWindowOnOff == ESlateVisibility::Hidden ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}

	ESlateVisibility GetStatusWindowOnOff()
	{
		return StatusWindowOnOff;
	}

	void SetStatusWindowOnOff(ESlateVisibility _Visibility)
	{
		StatusWindowOnOff = _Visibility;
	}

private:
	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility StatusWindowOnOff = ESlateVisibility::Hidden;

	UPROPERTY(Category = "Effect", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ESlateVisibility TalkTextWindowOnOff = ESlateVisibility::Hidden;
};
