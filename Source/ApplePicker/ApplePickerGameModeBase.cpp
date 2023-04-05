// Copyright Epic Games, Inc. All Rights Reserved.


#include "ApplePickerGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "BaseBasket.h"
#include "BaseApple.h"
#include "BaseAppleTreeParent.h"
#include "TreeBase.h"
#include "Widgets/BaseWidgetApplePicker.h"

void AApplePickerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// If we have the game widget type  
	if (GameWidgetType)
	{
		Widget = Cast<UBaseWidgetApplePicker>(CreateWidget(GetWorld(), GameWidgetType));
		if (Widget)
		{
			Widget->AddToViewport();
			UpdateWidgetText();
		}
	}

	Basket = Cast<ABaseBasket>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (Basket)
	{
		Basket->DisableInput(nullptr);
	}

	FTimerHandle GameStartTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(GameStartTimerHandle
		, this
		, &AApplePickerGameModeBase::HandleGameStart
		, GameStartDelay
		, false);

}

void AApplePickerGameModeBase::HandleAppleCaught()
{
	ApplesCaught += 1;
	UpdateWidgetText();
	UE_LOG(LogTemp, Warning, TEXT("Apple Caught: %d"), ApplesCaught);

	if (ApplesCaught >= ApplesToWin)
	{
		this->HandleGameOver(true);
		if (Widget)
		{
			Widget->SetGameOverText(true);
		}
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
		if (Widget)
		{
			Widget->SetGameOverText(false);
		}
	}

}

float AApplePickerGameModeBase::GetGameStartDelay() const
{
	return GameStartDelay;
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


void AApplePickerGameModeBase::HandleGameStart()
{
	// static class return an object representing that class at the runtime
	TArray<AActor*> AppleTreesParentFounded;
	UGameplayStatics::GetAllActorsOfClass(GetWorld()
		, ABaseAppleTreeParent::StaticClass()
		, AppleTreesParentFounded);

	for (auto ptr : AppleTreesParentFounded)
	{
		// start tree functions
		if (ATreeBase* Tree = Cast<ATreeBase>(ptr))
		{
			Tree->StartAppleDrops();
			Tree->StartRedirecting();
		}
	}
	if (Basket && Basket->GetBasketPlayerController())
	{
		Basket->EnableInput(Basket->GetBasketPlayerController());
		Basket->SetActorTickEnabled(true);
	}
}

void AApplePickerGameModeBase::UpdateWidgetText()
{
	if (Widget)
	{
		Widget->SetApplesCollectedText(ApplesCaught, ApplesToWin);
	}
}
