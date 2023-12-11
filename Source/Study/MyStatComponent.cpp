// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	bWantsInitializeComponent = true;
	Level = 1;
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

void UMyStatComponent::SetLevel(int32 _lvl)
{
	auto ins = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (ins)
	{
		auto data = ins->GetStatData(Level);
		
		if (data)
		{
			Level = data->Level;
			Attack = data->Attack;
			SetHp(data->MaxHp);
			MaxHp = data->MaxHp;
		}
	}
}

void UMyStatComponent::SetHp(int32 _new)
{
	if (Hp == _new)
		return;

	Hp = _new > 0 ? _new : 0;
	OnHpChanged.Broadcast();
}

void UMyStatComponent::OnAttacked(float _DamAmt)
{
	SetHp(Hp - _DamAmt);

	UE_LOG(LogTemp,Warning,TEXT("ATTACKED %d"),Hp);

}


