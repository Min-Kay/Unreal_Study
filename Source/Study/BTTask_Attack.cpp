// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "MyAIController.h"
#include "MyCharacter.h"


UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true; // TickTask ��� ���� ����
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Result = Super::ExecuteTask(OwnerComp,NodeMemory);

	auto MyChar = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == MyChar)
		return EBTNodeResult::Failed;

	MyChar->Attack();
	bIsAttacking = true;

	// ��������Ʈ�� Ȱ���� ���� �ִϸ��̼��� ������ �ο� ��ȯ
	MyChar->OnAttackEnd.AddLambda([this]() {
		bIsAttacking = false;
		});

	return Result;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,NodeMemory,DeltaSeconds);

	if (false == bIsAttacking)
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
}
