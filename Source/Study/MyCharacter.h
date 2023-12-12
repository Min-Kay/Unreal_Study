// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEnd);

UCLASS()
class STUDY_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	virtual void Jump();

	void Attack();

	FOnAttackEnd OnAttackEnd;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
public:
	void Set_CanJump(bool _jump) { CanJumping = _jump; }
	void AttackCheck();

private:
	UPROPERTY(VisibleAnyWhere)
	class USpringArmComponent* SpringArm = nullptr;
	
	UPROPERTY(VisibleAnyWhere)
	class UCameraComponent* Camera = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = pawn)
	bool CanJumping = false;

	UPROPERTY(VisibleAnyWhere,Category = pawn)
	bool IsAttacking = false;

	UPROPERTY()
	class UMyAnimInstance* AnimInstance = nullptr;

	UPROPERTY()
	int32 AttackIndex = 0;

public:
	UPROPERTY()
	float Horizontal = 0.f;

	UPROPERTY()
	float Vertical = 0.f;

	UPROPERTY(VisibleAnywhere)
	class UMyStatComponent* Stat;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;

};
