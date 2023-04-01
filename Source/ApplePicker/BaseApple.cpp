// Fill out your copyright notice in the Description page of Project Settings.

#include "ApplePickerGameModeBase.h"
#include "BaseApple.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseApple::ABaseApple()
	:LowerBound(-680.0f), CurrentGameMode(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AppleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMeshComponent"));

	RootComponent = AppleMeshComponent;

}

// Called when the game starts or when spawned
void ABaseApple::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameMode = Cast<AApplePickerGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ABaseApple::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Can use trigger box instead
	FVector AppleLocation = GetActorLocation();
	if (AppleLocation.Z < LowerBound)
	{
		if (CurrentGameMode)
		{
			CurrentGameMode->HandleAppleLost();
		}
		this->Destroy();
	}

}

