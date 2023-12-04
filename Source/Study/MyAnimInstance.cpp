// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

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
	}
}
