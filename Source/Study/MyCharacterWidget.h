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

	// meta BindWidget를 이용해 변수명과 동일한 위젯을 찾아 삽입해준다.
	// BindWidget 외에는 GetWidgetFromName 함수로 캐스팅 해와야한다.
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;
};
