// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT(TEXT("DataTable'/Game/Data/StatTable.StatTable'"));

	if (DT.Succeeded())
	{
		MyStats = DT.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp,Warning,TEXT("MyGameInstance %d"),GetStatData(1)->Attack)
}

FMyCharacterData* UMyGameInstance::GetStatData(int32 Level)
{
	return MyStats->FindRow<FMyCharacterData>(*FString::FromInt(Level), TEXT(""));
}
