// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include "Global/GlobalGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	JumpMaxHoldTime = 0.0f;

	// �𸮾��� ������Ʈ��°��� ������� �����ڿ����� ����� �ִ�.
	// �� ������ �ִµ� �ӷ¶����̴�. 
	// �𸮾��� �ӷ¶����� ������ �����ڿ����� ������Ʈ�� �ް� �����.
	// CDO������ �����ؾ� �Ѵ�.
	// CreateDefaultObject�Դϴ�.
	// ������� �������� �Դϴ�.

	// �����ڿ��� ������Ʈ�� ����� ����� ������ �Լ��� ����ϸ� �ȴ�.

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	// � �ٸ� �θ𿡰� ���� ���δٴ� �̾߱Ⱑ �˴ϴ�.
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("B_R_Weapon"));


	// �𸮾󿡰� �� �̸Ž� ����� ����Ұž�.
	// �����ڿ����� �����ϴ�.

	// WeaponArrays.Add();

	//{
	//	// �Ž��� ���ڴٰ� �ϴ°�.
	//	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoader(TEXT("/Script/Engine.StaticMesh'/Game/Resources/Test/Static/2Hand-Sword.2Hand-Sword'"));
	//	if (true == MeshLoader.Succeeded())
	//	{
	//		WeaponArrays.Add(MeshLoader.Object);
	//	}
	//}

	//{
	//	// �Ž��� ���ڴٰ� �ϴ°�.
	//	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshLoader(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));

	//	if (true == MeshLoader.Succeeded())
	//	{
	//		WeaponArrays.Add(MeshLoader.Object);
	//	}
	//}

	// CDO���� ���Ŀ� �������Ʈ �ʱ�ȭ�� �̷������ �Ǵµ�.
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	JumpMaxCount = 2;

	GetWorld()->GetAuthGameMode();

	UGlobalGameInstance* Inst = GetGameInstance<UGlobalGameInstance>();

	WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Weapon")));
	WeaponArrays.Add(GetGameInstance<UGlobalGameInstance>()->GetMesh(TEXT("Cube")));

	WeaponMesh->SetStaticMesh(WeaponArrays[0]);

	TArray<UActorComponent*> FindComponents = GetComponentsByTag(USceneComponent::StaticClass(), TEXT("RotComponent"));

	if (0 != FindComponents.Num())
	{
		USceneComponent* SceneCom = Cast<USceneComponent>(FindComponents[0]);

		UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(FindComponents[0]);
	}

	int a = 0;
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AniState != TPSAniState::Attack)
	{
		WeaponMesh->SetGenerateOverlapEvents(false);
	}
	else 
	{
		WeaponMesh->SetGenerateOverlapEvents(true);
	}

	// GetMovementComponent()->Velocity = FVector::LeftVector * 100.0f;

	// ���⼭�ϴ°� �����ϴ�.

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	static bool bBindingsAdded = false;
	if (!bBindingsAdded)
	{
		bBindingsAdded = true;

		// ������ ������ ����?
		// DefaultPawn_MoveForward �߰��Ǵ°� ��
		// ����θ� �ϰ� �ֽ��ϴ�.
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::W, 1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveForward", EKeys::S, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::A, -1.f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerMoveRight", EKeys::D, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerTurn", EKeys::MouseX, 1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerLookUp", EKeys::MouseY, -1.f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping("PlayerJumpAxis", EKeys::E, -1.f));


		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerAttack"), EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(TEXT("PlayerJumpAction"), EKeys::SpaceBar));
	}

	// Ű�� �Լ��� �����մϴ�.
	// �� Ű�� ������ �� �Լ��� ����������ε�.
	// ���϶��� �ϴ� ��� ���������.
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &ATPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &ATPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &ATPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &ATPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &ATPSCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &ATPSCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("PlayerJumpAxis", this, &ATPSCharacter::JumpAxis);

	PlayerInputComponent->BindAction("PlayerAttack", EInputEvent::IE_Pressed, this, &ATPSCharacter::AttackAction);
	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &ATPSCharacter::JumpAction);
}


void ATPSCharacter::MoveRight(float Val)
{
	if (AniState == TPSAniState::Attack || AniState == TPSAniState::Jump)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			// transform to world space and add it
			// ���� �� ȸ���� �����ͼ� y�࿡ �ش��ϴ� �຤�͸� ������ �̴ϴ�.
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);

			AniState = Val > 0.f ? TPSAniState::RightMove : TPSAniState::LeftMove;
			return;
		}
	}
	else
	{
		if (AniState == TPSAniState::RightMove || AniState == TPSAniState::LeftMove)
		{
			AniState = TPSAniState::Idle;
		}
	}
}

void ATPSCharacter::MoveForward(float Val)
{
	if (AniState == TPSAniState::Attack || AniState == TPSAniState::Jump)
	{
		return;
	}

	if (Val != 0.f)
	{
		if (Controller)
		{
			// ��Ʈ�ѷ��� �⺻������
			// charcter �ϳ��� �پ� �ֽ��ϴ�.
			FRotator const ControlSpaceRot = Controller->GetControlRotation();

			// �̰� ������ ���Դϴ�.
			// transform to world space and add it
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			// ž������̸� �ٸ��� ������ �Ǵµ�.
			// ������ TPS�� �ϰ� �ֱ� ������ ��Ʈ�ѷ��� ȸ���̳� ������ ȸ���̳� ���ƿ�.
			// AddMovementInput(GetActorForwardVector(), Val);

			AniState = Val > 0.f ? TPSAniState::ForwardMove : TPSAniState::BackwardMove;
			return;
		}
	}
	else 
	{
		if (AniState == TPSAniState::ForwardMove || AniState == TPSAniState::BackwardMove)
		{
			AniState = TPSAniState::Idle;
		}
	}

	// �̷� ������ �Լ� �� static�Լ��� �ǹ��Ѵ�.
	// AEGLOBAL::DebugPrint("AAAAAAA");
}


void ATPSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ATPSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}


void ATPSCharacter::JumpAxis(float Rate)
{
	if (0.0f == Rate)
	{
		if (true == AxisJump)
		{
			StopJumping();
			AxisJump = false;
		}
		return;
	}

	AxisJump = true;
	Jump();
}

void ATPSCharacter::JumpAction()
{
	// JumpCurrentCount
	UE_LOG(LogTemp, Log, TEXT("%S(%u)> %d"), __FUNCTION__, __LINE__, JumpCurrentCount);
	Jump();

	AniState = TPSAniState::Jump;
}

void ATPSCharacter::AttackAction()
{
	// �����Ʈ ������Ʈ�� ���ؼ� �Ѵ�.
	// GetMovementComponent()

	// PlayMontage();

	AniState = TPSAniState::Attack;
}

void ATPSCharacter::AnimationTick()
{
	//class UAnimMontage* Montage = AllAnimations[AniState];

	//if (nullptr == Montage)
	//{
	//	return;
	//}

	//if (false == GetMesh()->GetAnimInstance()->Montage_IsPlaying(Montage))
	//{
	//	GetMesh()->GetAnimInstance()->Montage_Play(Montage, 1.0f);
	//}
}
//
//void ATPSCharacter::MontageEnd(UAnimMontage* Anim, bool _Inter)
//{
//	// Anim ����� ��Ÿ��
//	if (AllAnimations[TPSAniState::Attack] == Anim)
//	{
//		AniState = TPSAniState::Idle;
//		GetMesh()->GetAnimInstance()->Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
//	}
//
//	if (AllAnimations[TPSAniState::Jump] == Anim)
//	{
//		AniState = TPSAniState::Idle;
//		GetMesh()->GetAnimInstance()->Montage_Play(AllAnimations[TPSAniState::Idle], 1.0f);
//	}
//
//	
//
//	// �� ���η� ������������ Ȯ���ؾ� �մϴ�.
//	int a = 0;
//}