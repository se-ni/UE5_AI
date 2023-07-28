// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/SnakeHead.h"
#include "SnakeGameMode.h"
#include "../Global/GlobalGameInstance.h"

// Sets default values
ASnakeHead::ASnakeHead()
{
	// �𸮾󿡼� �����Ӹ��� Tick�� ������ �ϴ� ���ʹ�
	// PrimaryActorTick.bCanEverTick = true; �� �������� Tick�� �������� �ֽ��ϴ�.
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// �����ڿ��� ���� �������ִ°� �Ϲ����ε�. 
	// ƽ�� �����ų� ���ų�
	PrimaryActorTick.bCanEverTick = true;
	// PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;


}

// Called when the game starts or when spawned
void ASnakeHead::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASnakeHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeHead::LeftMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}

	AddActorLocalOffset(FVector::LeftVector);
}


void ASnakeHead::RightMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}

	AddActorLocalOffset(FVector::RightVector);
}
void ASnakeHead::UpMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}
	AddActorLocalOffset(FVector::UpVector);
}
void ASnakeHead::DownMove(float _Value)
{
	if (0 == _Value)
	{
		return;
	}
	AddActorLocalOffset(FVector::DownVector);
}

void ASnakeHead::MoveLogic(const FVector& _MoveVector)
{
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation() + _MoveVector, "Wall"))
	{
		return;
	}

	{
		FVector HeadPos = GetActorLocation() + _MoveVector;
		FIntVector HeadIndex = FIntVector(HeadPos.X, HeadPos.Y, HeadPos.Z);

		ASnakePart* CurNextPart = GetNext();
		while (nullptr != CurNextPart)
		{
			// ����ؾ��Ұ� ���� ������?
			// �Ǽ��� 0�� �ƴϸ� �񱳰� ������ ���ؼ� �����Ҷ��� �ִ�.
			FVector BodyPos = CurNextPart->GetActorLocation();

			// �̷��� �ִ� ������?????
			// deltatime���� �̵��ϰ� ���� �ʱ� ������
			// ������ �����ؼ� ���ϸ� �񱳰� �����ϴٴ� 
			FIntVector BodyIndex = FIntVector(BodyPos.X, BodyPos.Y, BodyPos.Z);

			if (HeadIndex == BodyIndex)
			{
				UE_LOG(LogTemp, Error, TEXT("%S(%u)> Game End"), __FUNCTION__, __LINE__);
				return;
			}

			CurNextPart = CurNextPart->GetNext();
		}
	}

	SetPrevPos(GetActorLocation());

	AddActorLocalOffset(_MoveVector);

	{
		if (nullptr != GetNext())
		{
			ASnakePart* CurNextPart = GetNext();

			while (nullptr != CurNextPart)
			{
				CurNextPart->SetPrevPos(CurNextPart->GetActorLocation());
				CurNextPart->SetActorLocation(CurNextPart->GetPrev()->GetPrevPos());
				CurNextPart = CurNextPart->GetNext();
			}
		}
	}


	// ���⿡ Body�� �ִ��� Ȯ���ؾ� �Ѵ�.
	if (true == GetSnakeGameMode()->IsPart(GetActorLocation(), "Body"))
	{
		AActor* Body = GetSnakeGameMode()->GetPart(GetActorLocation(), "Body");
		ASnakePart* BodyPart = Cast<ASnakePart>(Body);

		if (nullptr == BodyPart)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Part)"), __FUNCTION__, __LINE__);
			return;
		}

		ASnakePart* LastPart = LastNextPart();
		// �ű��ڸ��� ���Ӹ�忡 ��ϵǾ�� �Ѵ�.
		BodyPart->SetActorLocation(LastPart->GetPrevPos());
		LastPart->SetNext(BodyPart);
		BodyPart->SetPrev(LastPart);
		GetSnakeGameMode()->CurBodyReset();
	}
}

void ASnakeHead::LeftAction()
{
	FVector MovePos = FVector::LeftVector * 100.0f;
	MoveLogic(MovePos);
}
void ASnakeHead::RightAction()
{
	FVector MovePos = FVector::RightVector * 100.0f;
	MoveLogic(MovePos);
}
void ASnakeHead::UpAction()
{
	FVector MovePos = FVector::UpVector * 100.0f;
	MoveLogic(MovePos);
}
void ASnakeHead::DownAction()
{
	FVector MovePos = FVector::DownVector * 100.0f;
	MoveLogic(MovePos);
}