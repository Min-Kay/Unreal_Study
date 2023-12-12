// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UBTTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindPatrolPos();

	 //실행 시 할 행동
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	

};
