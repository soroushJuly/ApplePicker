// Copyright Epic Games, Inc. All Rights Reserved.


#include "ApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BaseBasket.h"
#include "BaseApple.h"
#include "TreeBase.h"

void AApplePickerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Basket = Cast<ABaseBasket>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AApplePickerGameModeBase::HandleAppleCaught()
{
	ApplesCaught += 1;
	UE_LOG(LogTemp, Warning, TEXT("Apple Caught: %d"), ApplesCaught);
}

void AApplePickerGameModeBase::HandleAppleLost()
{
	ApplesLost += 1;
	UE_LOG(LogTemp, Warning, TEXT("Apple Lost: %d"), ApplesLost);

	if (Basket)
	{
		Basket->DestroyPaddle();
	}

	if (ApplesLost >= 3)
	{

		// stop spawing apples
		TArray<AActor*> TreesFounded;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATreeBase::StaticClass(), TreesFounded);
		for (auto ptr : TreesFounded)
		{
			ATreeBase* Tree = Cast<ATreeBase>(ptr);
			if (Tree)
			{
				Tree->StopAppleDrops();
			}
		}

		// destroy remaining apples
		// static class return an object representing that class at the runtime
		TArray<AActor*> ApplesFounded;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseApple::StaticClass(), ApplesFounded);

		for (auto ptr : ApplesFounded)
		{
			ABaseApple* Apple = Cast<ABaseApple>(ptr);
			if (Apple)
			{
				Apple->Destroy();
			}
		}
	}

}
