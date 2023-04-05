// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ApplePickerGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class APPLEPICKER_API AApplePickerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void HandleAppleCaught();
	void HandleAppleLost();

	UFUNCTION(BlueprintCallable)
		float GetGameStartDelay() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
		void HandleGameOver(bool bWonGame);
	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 ApplesToWin {
		4
	};

	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 ApplesToLose {
		3
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float GameStartDelay{ 5.0f };

	// To specify widget blueprint in Editor
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> GameWidgetType;

	UPROPERTY()
		class UBaseWidgetApplePicker* Widget;
private:
	int32 ApplesCaught{ 0 };
	int32 ApplesLost{ 0 };

	// it is better to null the pointers instead of garbage value
	class ABaseBasket* Basket{ nullptr };

	void HandleGameStart();

	void UpdateWidgetText();
};
