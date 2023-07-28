// Fill out your copyright notice in the Description page of Project Settings.


#include "MathGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MathWidget.h"

void AMathGameMode::AddDebugText(const FString& _Text)
{
	DebugWidget->CPText += _Text + TEXT("\n");
}

void AMathGameMode::BeginPlay()
{
	{
		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Main", AllActor);

		if (1 != AllActor.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> Main Actor Is nullptr"), __FUNCTION__, __LINE__);
			return;
		}

		MainActor = AllActor[0];
	}

	// � Ŭ������ ���� 
	// ������ ���� Ŭ������� 
	GetGameInstance();

	{
		// �ѹ��� �Ϻ��ϰ� ġ�������� �ʴ´�. 
		// ���¿� ����� �ڵ带 ġ��
		// ����ó���� ��û �Ű�Ἥ ���ش�.
		// ���ܿ� �ɸ��� ���� ���߸� �ߴ��� �˾Ƴ��Եǰ�
		// ������ �����鼭 �Ϻ��� �ڵ尡 �ǰ� �ȴ�.
		
		// �ѹ��� �Ϻ��� �ڵ带 ġ���� ������� ������
		// �׳� �ƹ��͵� ���ϴ°�ó�� ���δ�.
		// �� ��Ÿ���� ������� ���� ����� ���մϴ�.
		// 10�и��� �����Ϸ� 20�и��� �Ϻ��� �ڵ� ��ħ.
		// ����� ����. => �ڵ带 �׳� ��ġ�� �ִ�.
		
		// ������ �ɰ��� �ϳ��ϳ��� ������
		// �̰� ���۾��ϴ� ��Ȳ�� ���ܸ� �� �ɾ���´�.
		// �ѹ��ڱ��� �������� ����� �ְ�
		// �ڽ��� ���� �ڵ带 �����ߴ��� ��

		TArray<AActor*> AllActor;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Other", AllActor);

		if (1 != AllActor.Num())
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> Main Actor Is nullptr"), __FUNCTION__, __LINE__);
			return;
		}

		OtherActor = AllActor[0];

		OriPos = OtherActor->GetActorLocation();
	}

}

void AMathGameMode::Reset()
{
	OtherActorState = OtherState::Idle;
	OtherActor->SetActorLocation(OriPos);
}

void AMathGameMode::Tick(float _Delta) 
{
	if (nullptr == MainActor || nullptr == OtherActor)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == MainActor || nullptr == OtherActor)"), __FUNCTION__, __LINE__);
		return;
	}

	switch (OtherActorState)
	{
	case OtherState::Idle:
	{
		break;
	}
	case OtherState::LocalTrace:
	{
		// ������ ���ϰ�
		FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
		// ������ �������ͷ� �����
		Dir.Normalize();
		// �̷����� �ϸ� ����� �ȵ�.
		// �׳� 1�κ����ݾƿ�? 
		// �ð��� ����ȵ����Ƿ� ��ǻ���� ���ɸ��� �ٸ��� �����̰� �ȴ�.
		// �̷��� ���ְ� ���⿡ ���� �����ϴ� �ӷ��� �־ ������� �մϴ�.
		//                                  ����                �ð�    �ӵ�

		// �̷� �̵��� ������ ��� ��Դϴ�.
		// ������ �ڱ��ڽ��� �߽��� �Ǽ� ��ǥ�踦 ����µ�
		// �ڽ��� ȸ���ϰ� �Ǹ� ��ǥ�赵 ���� ȸ���� �ϰ� �ɰ̴ϴ�.
		OtherActor->AddActorLocalOffset(Dir * _Delta * 2000.0f);
		break;
	}
	case OtherState::WorldTrace:
	{
		// ������ ���ϰ�
		FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
		Dir.Normalize();
		// ����� ���״�� ���� ��ǥ�迡���� ������ �ϰ�
		OtherActor->AddActorWorldOffset(Dir * _Delta * 500.0f);
		break;
	}
	case OtherState::Jump:
	{
		// �̹� ���� ������ �̴� �Ŷ� �ð��� ����Ǹ� �˴ϴ�.
		// �𸮾� �������� ��������ƽ�� ������ ������ �ʱ�ȭ�� ���� �ʴ´�.
		// �� �̹� ���ϰ� �ٿ�� ���� �״�� ������ �ȴ�.
		// static�� �� �׷��� ó���� �ǹǷ� �Ϲ����� static �ɹ������� �����ؼ� ����ؾ� �Ѵ�.
		// ��? ����ǰ� �� ���Ŀ� �ٽ� �ʱ�ȭ�� ���� �ʱ� �����̴�.
		// static FVector UpVector = {5000, 0, 0};
		FVector Gravity = { -3000, 0, 0 };
		UpVector += Gravity * _Delta;

		FVector LastVector = UpVector;
		OtherActor->AddActorWorldOffset(LastVector * _Delta);
		break;
	}
	case OtherState::PTrace:
	{
		FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();
		Dir.Normalize();
		//                          ���ӵ�
		PTraceDir += Dir * _Delta * 1000.0f;

		// �ִ� �ӷ��� ������ �ɾ�� �մϴ�.

		if (700.0f <= PTraceDir.Length())
		{
			// �ӷ��� �����ϴ� ����.
			PTraceDir.Normalize();
			PTraceDir *= 700.0f;
		}

		OtherActor->AddActorWorldOffset(PTraceDir * _Delta);
		break;
	}
	case OtherState::Look:
	{
		// ���� ������ �����ϴµ�.
		// �𸮾��������� 
		// ������ �־��ָ� �� ������ �ٶ󺸰� ����� �Լ��� �־��
		FVector Dir = MainActor->GetActorLocation() - OtherActor->GetActorLocation();

		// FQuat ������μ� ���Ҽ���� ȸ������� ���.
		// ȸ���� ���̴� �ڷ����߿� �ϳ�
		
		// FRotator Rot;
		// ����� => �������Ͱ� �ɼ� �ְ�
		// FQuat => FRotator
		// FRotator => FQuat �ɼ� �ִ� �Լ��� ���ΰ� ������ �ִ�.

		// ������ �ִٸ� �ű⿡�� �ٷ� �����̼��� ���� �ְ� ����� ����.
		FRotator Rot = Dir.Rotation();
		// �̹����� Set�̴� ���� => �ѹ��� ��븦 �ٶ���� �ϴϱ�.
		OtherActor->SetActorRotation(Rot);
		break;
	}
	case OtherState::AngleRot:
	{
		// 360�� �������� ������ ����� �ִ�.
		FRotator Rot = FRotator::MakeFromEuler({0, 0, 360.0f * _Delta });
		// ������ ȸ����Ű�� �⺻���� ȸ��
		OtherActor->AddActorWorldRotation(Rot);
		// OtherActor->Look(MainActor);
		break;
	}
	case OtherState::AngleLook:
	{
		// ��κ� �����ϴ°��� 3D�����̶�� �ص� ������ �����ϰ� ȸ���ϴ� ��찡 ��κ��̴�.
		FVector MainPos = MainActor->GetActorLocation();
		FVector OtherPos = OtherActor->GetActorLocation();
		// Ȥ�ö� z���� ���� ���ɼ��� ���ִ°� �����Դϴ�.
		MainPos.Z = 0.0f;
		OtherPos.Z = 0.0f;

		FVector Dir = MainPos - OtherPos;
		Dir.Normalize();

		FVector OtherForward = OtherActor->GetActorForwardVector();
		OtherForward.Normalize();

		FVector Cross = FVector::CrossProduct(OtherForward, Dir);

		// �̵��̰� ȸ���̰� �׳� ������ ���θ�

		// HeadingAngle
		float Angle0 = Dir.Rotation().Yaw;
		float Angle1 = OtherForward.Rotation().Yaw;

		UE_LOG(LogTemp, Log, TEXT("%S(%u)> [%f][%f]"), __FUNCTION__, __LINE__, Angle0, Angle1);

		// FString�� ���� ���ڿ��� ó���Ҷ� + ���� �����ڸ� �̿��ؼ�
		// ���� ����� ���ڿ��� ����� ���� �ִ�.
		FString Str = "Dir Angle : ";
		Str += FString::SanitizeFloat(Angle0);
		AddDebugText(Str);

		// ������ z���� ���Ѱ� �߿��Ѱ� �ƴ���? ������ ������� ������ ���Ͱ� ������
		// ������ ���ŵǾ� �־�� �Ѵ�.
		if (FMath::Abs(Angle0 - Angle1) >= 1.0f)
		{
			FRotator Rot = FRotator::MakeFromEuler({ 0, 0, Cross.Z * 100.0f * _Delta });
			OtherActor->AddActorWorldRotation(Rot);
		}
		else {
			FRotator Rot = Dir.Rotation();
			OtherActor->SetActorRotation(Rot);
		}
		// AngleText = FString::SanitizeFloat(Angle, 10);

		// ���� ���ȿ� �����Ѵٴ°��� �߿��ϴ�. ������ z�� 0�̶�� ������ ��ġ�ϱ� ������ 
		// XYZ�� ���� �ٸ��� ȸ���ؾ��� ������ 3���� ���;� �մϴ�.
		// �ϳ��� �ุ �����ص� ȸ���ؾ��ϴ� ������ 1���� �ٰԵ˴ϴ�.
	}
	default:
		break;
	}
}