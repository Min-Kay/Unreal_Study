// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"
#include "MyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos"); // 블루프린트에서 사용할 명칭
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Result = Super::ExecuteTask(OwnerComp,NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == CurrentPawn)
		return EBTNodeResult::Failed;

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem)
		return EBTNodeResult::Failed;

	FNavLocation RandomLoc;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, RandomLoc))
	{
		// 블랙보드 내의 키에 값을 저장
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")),RandomLoc.Location);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
