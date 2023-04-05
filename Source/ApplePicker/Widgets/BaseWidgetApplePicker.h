// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidgetApplePicker.generated.h"

/**
 *
 */
UCLASS()
class APPLEPICKER_API UBaseWidgetApplePicker : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetApplesCollectedText(int32 ApplesCollected, int32 ApplesToCollect);

	UFUNCTION(BlueprintImplementableEvent)
		void SetGameOverText(bool bWonGame);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float GameStartDelay{ 5.0f };
};
