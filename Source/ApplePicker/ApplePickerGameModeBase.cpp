// Copyright Epic Games, Inc. All Rights Reserved.


#include "ApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BaseBasket.h"
#include "BaseApple.h"
#include "BaseAppleTreeParent.h"
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

	if (ApplesLost >= ApplesToWin)
	{
		this->HandleGameOver(true);
	}
}

void AApplePickerGameModeBase::HandleAppleLost()
{
	ApplesLost += 1;
	UE_LOG(LogTemp, Warning, TEXT("Apple Lost: %d"), ApplesLost);

	if (Basket)
	{
		Basket->DestroyPaddle();
	}

	if (ApplesLost >= ApplesToLose)
	{
		this->HandleGameOver(false);
	}

}

// if we want to use it in blueprints we should use parent fuction by right clicking on the node
void AApplePickerGameModeBase::HandleGameOver_Implementation(bool bWonGame)
{
	// static class return an object representing that class at the runtime
	TArray<AActor*> AppleTreesParentFounded;
	UGameplayStatics::GetAllActorsOfClass(GetWorld()
		, ABaseAppleTreeParent::StaticClass()
		, AppleTreesParentFounded);

	for (auto ptr : AppleTreesParentFounded)
	{
		//ATreeBase* Tree = Cast<ATreeBase>(ptr);
		// stop spawing apples
		if (ATreeBase* Tree = Cast<ATreeBase>(ptr))
		{
			Tree->StopAppleDrops();
		}
		else if (ABaseApple* Apple = Cast<ABaseApple>(ptr))
		{
			// destroy remaining apples
			Apple->Destroy();
		}
	}

	if (Basket && Basket->GetBasketPlayerController())
	{
		// Disabling accepting input for the basket after loss
		// if nullptr passed disable input from all controller 
		Basket->DisableInput(Basket->GetBasketPlayerController());

		// in case if a player holds a key in the last frame of the lossing
		Basket->SetActorTickEnabled(false);
	}
}
