// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

	// AI의 빙의 - 탈출에 대해서 지원한다
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	void RandomMovement();

private:
	FTimerHandle TimerHandle; // 핸들을 활용해 빙의 해제를 요청함

	UPROPERTY()
	class UBehaviorTree* BehaviorTree;

	UPROPERTY()
	class UBlackboardData* BlackboardData;
};
