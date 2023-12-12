// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/AI/BT_MyCharacter.BT_MyCharacter'"));

	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("BlackboardData'/Game/AI/BB_MyCharacter.BB_MyCharacter'"));

	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);



	if (UseBlackboard(BlackboardData, Blackboard))
	{
		if (RunBehaviorTree(BehaviorTree))
		{
			// TODO
		}
	}
	else {
		//GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AMyAIController::RandomMovement,3.f,true);
		//3초마다 명령 실행토록 예약
	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle); // 해제
}

void AMyAIController::RandomMovement()
{
	auto CurrentPawn = GetPawn();

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
		return;

	FNavLocation RandomLoc;
	// 내비 메쉬 볼륨을 설치해야 가능함
	// 내비게이션으로부터 범위 내 무작위 좌표를 받음
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLoc))
	{
		// 좌표로 이동
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this,RandomLoc);
	}
}
