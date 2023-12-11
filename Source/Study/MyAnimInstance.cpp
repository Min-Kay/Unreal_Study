// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/PawnMovementComponent.h"



UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Anims/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));
	
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSecond)
{
	Super::NativeUpdateAnimation(DeltaSecond);

	auto pawn = TryGetPawnOwner();

	if (!IsValid(pawn))
		return;

	Speed = pawn->GetVelocity().Size();

	auto Character = Cast<ACharacter>(pawn);

	if (Character)
	{
		IsFalling = Character->GetMovementComponent()->IsFalling();
		PressJump = Character->bPressedJump;

		auto MyChar = Cast<AMyCharacter>(Character);

		if (MyChar)
		{
			MyChar->Set_CanJump(JumpEnd && !IsFalling);
			Horizontal = MyChar->Horizontal;
			Vertical = MyChar->Vertical;
		}
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage,1.f);
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name,AttackMontage);
}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"),SectionIndex));
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	//UE_LOG(LogTemp,Log,TEXT("Attack"));
	OnAttackHit.Broadcast();
}

void UMyAnimInstance::AnimNotify_JumpEnding()
{
	//UE_LOG(LogTemp, Log, TEXT("JE"));
	OnJumpEnding.Broadcast();
	JumpEnd = true;
}
