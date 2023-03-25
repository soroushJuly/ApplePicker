// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"

// Sets default values
ATreeBase::ATreeBase()
	:MovementSpeed(550.0f), Boundary(800.0f), RedirectChance(0.4f), RedirectTime(1.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TreeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMeshComponent"));

	RootComponent = TreeMeshComponent;

}

// Called when the game starts or when spawned
void ATreeBase::BeginPlay()
{
	Super::BeginPlay();

	srand(time(0));

	GetWorld()->GetTimerManager().SetTimer(ChangeDirectionTimer, this, &ATreeBase::ChangeDirection, RedirectTime, true, 2.5f);
}

// Called every frame
void ATreeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TempLocation{ GetActorLocation() };

	//if (isReachedBoundaries())
	if (FMath::Abs(TempLocation.Y) > Boundary)
	{
		ATreeBase::ChangeDirection();
	}


	// add offset
	TempLocation.Y += MovementSpeed * DeltaTime;

	// set actor location
	SetActorLocation(TempLocation);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), FVector::ToString(TempLocation));

}

void ATreeBase::ChangeDirection()
{
	if (FMath::FRand() <= RedirectChance)
	{
		MovementSpeed = -1 * MovementSpeed;
	}
}

