// Fill out your copyright notice in the Description page of Project Settings.


#include "EDULevelMode.h"

AEDULevelMode::AEDULevelMode() 
{

}

void AEDULevelMode::BeginPlay() 
{
	// �𸮾��� C++ �����Ϸ��� ���� �����س���. 
	// AGameMode::BeginPlay();
	Super::BeginPlay();

	// �𸮾��� �α׸� ���� ���
	// UE_LOG(LogTemp, Error, TEXT("���Ӹ�尡 ����������ϴ�."));
	// 
	
	UE_LOG(LogTemp, Log, TEXT("Test Log")); // ���
	UE_LOG(LogTemp, Warning, TEXT("Test Error")); // �����
	UE_LOG(LogTemp, Error, TEXT("Test Error")); // ������
	// UE_LOG(LogTemp, Fatal, TEXT("Test Error")); // ��¥ ������ ������Ų��.


	// ������ �ߴٸ� �ߴ����� �ɾ Ȯ���ϰ� ���� ���̴�.
	
}