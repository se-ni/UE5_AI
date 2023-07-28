// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/CollisionCharacter.h"
#include "Components/CapsuleComponent.h"
#include <Global/ARGlobal.h>

// Sets default values
ACollisionCharacter::ACollisionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollisionCharacter::BeginPlay()
{
	Super::BeginPlay();

	// �浹�� �̺�Ʈ�� ���浹 ������Ʈ���� ��������� �մϴ�.

	// UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&ACollisionCharacter::BeginOverLap);
	
}

// Called every frame
void ACollisionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �𸮾󿡼� Trace�浹�� ���带 ���ؼ� �����ؾ��Ѵ�.

	// �Ʒ��� �Լ����� ���� �̼��� �浹ü�� ����� ����̴�.

	// GetWorld()->LineTraceSingleByProfile

	// �� ���Լ��� �� ������ �ϴ°�?
	
	// �� �Լ��� ���� � �Լ��μ� �ľ��ϰ� �ִ°�?

	TArray<FHitResult> OutHits; // ����� �޴� �ڷᱸ��
	FVector Start = GetActorLocation() - FVector(0.0f, 0.0f,GetCapsuleComponent()->GetScaledCapsuleHalfHeight()); // ���� ����
	FVector End = GetActorLocation() + (-GetActorUpVector() * 1000000.0f); // ���� ��
	FName ProfileName = TEXT("GroundCheck"); // ���� �浹�� �浹 ������
	                                     // �浹�� üũ�ؼ� �ٸ� ������Ʈ���� �ľ��� ������

	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam;

	GetWorld()->LineTraceMultiByProfile(OutHits, Start, End, ProfileName, Params);

	if (0 != OutHits.Num())
	{
		{
			FString Text;
			Text = OutHits[0].GetActor()->GetName();
			UARGlobal::ARDebugTextPrint(this, Text);
		}

		{
			FString Text = "Dis : ";
			Text += FString::SanitizeFloat(OutHits[0].Distance);
			UARGlobal::ARDebugTextPrint(this, Text);
		}
	}

}

// Called to bind functionality to input
void ACollisionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
	PlayerInputComponent->BindAxis("PlayerMoveForward", this, &ACollisionCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerMoveRight", this, &ACollisionCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PlayerTurn", this, &ACollisionCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("PlayerTurnRate", this, &ACollisionCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("PlayerLookUp", this, &ACollisionCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("PlayerLookUpRate", this, &ACollisionCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("PlayerJumpAction", EInputEvent::IE_Pressed, this, &ACollisionCharacter::JumpAction);
}



void ACollisionCharacter::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
			return;
		}
	}
}

void ACollisionCharacter::MoveForward(float Val)
{
	if (Val != 0.f)
	{
		if (Controller)
		{
			FRotator const ControlSpaceRot = Controller->GetControlRotation();
			AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
			return;
		}
	}
}


void ACollisionCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}

void ACollisionCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() * CustomTimeDilation);
}


void ACollisionCharacter::JumpAction()
{
	Jump();
}



void ACollisionCharacter::BeginOverLap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// ���� ��ģ ������Ʈ�� �ı��Ǳ⸦ ���Ѵ�.

	if (OtherActor->ActorHasTag(TEXT("ItEM")))
	{
		OtherActor->Destroy();
	}

	// OverlappedComponent �浹�� �� ���Ͱ� ������ �ִ� ������Ʈ 
	// OtherActor �浹�� ��� actor => Item
	// OtherComp �浹�� ��� ������Ʈ

	// int32 OtherBodyIndex, ���� ������������ ���� �߿����� �ʱ� ������ pass
	// bool bFromSweep, ���� ������������ ���� �߿����� �ʱ� ������ pass


	// FHitResult �� �浹�� ���� ���� ������ ������ �ִ�.
	SweepResult.Distance;
	// �浹üũ�� ���ؼ� �ľǵ� ������ �Ÿ�
	SweepResult.FaceIndex;
	// �浹�� ���� ��ȣ
	SweepResult.GetActor();
	// �浹�� ����

}
