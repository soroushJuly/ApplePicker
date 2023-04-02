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
private:
	int32 ApplesCaught{ 0 };
	int32 ApplesLost{ 0 };

	// it is better to null the pointers instead of garbage value
	class ABaseBasket* Basket{ nullptr };
};
