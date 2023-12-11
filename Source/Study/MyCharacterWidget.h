// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class STUDY_API UMyCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Bind_Hp(class UMyStatComponent* StatComp);
	void UpdateHp();

private:
	TWeakObjectPtr<class UMyStatComponent> CurrStatComp;

	// meta BindWidget�� �̿��� ������� ������ ������ ã�� �������ش�.
	// BindWidget �ܿ��� GetWidgetFromName �Լ��� ĳ���� �ؿ;��Ѵ�.
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;
};
