// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "MyAIController.h"
#include "MyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f; // Tick 주기를 설정한다.
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// 매 프레임마다 실행하진 않고 정해진 틱마다 실행한다.
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == CurrentPawn)
		return;
	
	UWorld* World = CurrentPawn->GetWorld();
	FVector Center = CurrentPawn->GetActorLocation();
	float SearchRadius = 500.f;

	if (nullptr == World)
		return;

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);

	bool bResult = World->OverlapMultiByChannel(OverlapResults,Center,
		FQuat::Identity,ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),QueryParams);

	AMyCharacter* MyChar = nullptr;
	FColor Color = FColor::Red;

	if (bResult) {
		for (auto& OverlapResult : OverlapResults)
		{
			auto TempChar = Cast<AMyCharacter>(OverlapResult.GetActor());

			if (TempChar && TempChar->GetController()->IsPlayerController())
			{
				MyChar = TempChar;
				Color = FColor::Green;
				break;
			}
		}
	}

	DrawDebugSphere(World, Center, SearchRadius, 16, Color, false, 0.2f);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), MyChar);
}
