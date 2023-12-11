// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterWidget.h"
#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacterWidget::Bind_Hp(UMyStatComponent* StatComp)
{
	// PB_HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	CurrStatComp = StatComp;
	StatComp->OnHpChanged.AddUObject(this,&UMyCharacterWidget::UpdateHp);
}

void UMyCharacterWidget::UpdateHp()
{
	if (!CurrStatComp.IsValid())
		return;

	PB_HpBar->SetPercent(CurrStatComp->GetHpRatio());
}
