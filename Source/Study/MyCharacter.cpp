// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "MyWeapon.h"
#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyCharacterWidget.h"
#include "MyAIController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	/*UE_LOG(LogTemp, Log, TEXT("hand_l_Soc"));
	FName WeapSoc(TEXT("hand_l_Soc"));
	if (GetMesh()->DoesSocketExist(WeapSoc))
	{
		UE_LOG(LogTemp, Log, TEXT("Weap"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SWM(TEXT("StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));

		if (SWM.Succeeded())
		{
			UE_LOG(LogTemp, Log, TEXT("Weap Suc"));
			Weapon->SetStaticMesh(SWM.Object);
		}

		Weapon->SetupAttachment(GetMesh(), WeapSoc);
	}*/

	Stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f,0.f,200.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (UW.Succeeded())
	{
		HpBar->SetWidgetClass(UW.Class); 
		HpBar->SetDrawSize(FVector2D(200.f,50.f));
	}

	// AI 조작을 가능케 해줌 -> Pawn에서 기본 제공
	AIControllerClass = AMyAIController::StaticClass(); 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; // 자동 빙의 조건
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//FName WeapSoc(TEXT("hand_l_soc"));
	//auto Weapon = GetWorld()->SpawnActor<AMyWeapon>(FVector::ZeroVector,FRotator::ZeroRotator);

	//if (Weapon)
	//{
		//Weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeapSoc);
	//}
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	}

	// UI 초기화
	HpBar->InitWidget();

	auto HpWidget = Cast<UMyCharacterWidget>(HpBar->GetUserWidgetObject());

	if (HpWidget)
		HpWidget->Bind_Hp(Stat);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Log, TEXT("CJ = %d"), CanJumping);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 기본 제공되는 점프 기능 사용
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed,this, &AMyCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
}

void AMyCharacter::UpDown(float Value)
{
	if (IsAttacking || !CanJumping)
		return;

	Vertical = Value;
	if (0 == Value)
		return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::LeftRight(float Value)
{
	if (IsAttacking || !CanJumping)
		return;

	Horizontal = Value;
	if (0 == Value)
		return;

	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Yaw(float Value)
{
	if (IsAttacking)
		return;

	if (0 == Value)
		return;

	// 따로 SpringArm에 설정하지 않아도 회전하는 이유는 Pawn 설정에 Use Controller Rotation Yaw 체크 박스가 디폴트 활성화 된다
	AddControllerYawInput(Value);
}

void AMyCharacter::Jump()
{
	if (IsAttacking && !CanJumping)
		return;

	Super::Jump();
}

void AMyCharacter::Attack()
{
	if (IsAttacking)
		return;

	AnimInstance->PlayAttackMontage();
	AnimInstance->JumpToSection(AttackIndex); 
	AttackIndex = (AttackIndex + 1) % 3;

	IsAttacking = true;
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	
	OnAttackEnd.Broadcast();
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);
	return DamageAmount;
}

void AMyCharacter::AttackCheck()
{
	FHitResult  HitResult;
	FCollisionQueryParams Params(NAME_None,false,this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	auto bResult = GetWorld()->SweepSingleByChannel(HitResult,GetActorLocation(), 
		GetActorLocation() + GetActorForwardVector() * AttackRange, 
		FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	FVector Vec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(),Center,HalfHeight,AttackRadius,Rotation,DrawColor,false,2.f);

	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp,Log,TEXT("Hit Actor : %s"),*HitResult.Actor->GetName());

		FDamageEvent De;
		HitResult.Actor->TakeDamage(Stat->GetAttack(),De,GetController(),this);
	}
}

