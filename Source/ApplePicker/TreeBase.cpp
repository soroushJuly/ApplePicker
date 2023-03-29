// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeBase.h"
#include "BaseApple.h"

// Sets default values
ATreeBase::ATreeBase()
	:MovementSpeed(550.0f), OuterBoundary(850.0f), InnerBoundary(600.0f), RedirectChance(0.4f), RedirectTime(1.0f), DropsInterval(1.0f)
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
	GetWorld()->GetTimerManager().SetTimer(AppleDropsTimer, this, &ATreeBase::DropApple, DropsInterval, true, 2.05f);
}

// Called every frame
void ATreeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TempLocation{ GetActorLocation() };

	//if (isReachedBoundaries())
	if (FMath::Abs(TempLocation.Y) > OuterBoundary)
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
	FVector TempPosition = GetActorLocation();
	if ((TempPosition.Y <= InnerBoundary && TempPosition.Y >= -InnerBoundary)) {
		if (FMath::FRand() <= RedirectChance)
		{
			MovementSpeed = -1 * MovementSpeed;
		}
	}
}

void ATreeBase::DropApple()
{
	// get tree base current location
	FVector TreeLocation{ GetActorLocation() };
	FRotator TreeRotation{ GetActorRotation() };

	// add a random number to the location within the range of tree
	if (FMath::FRand() < 0.6f &&)
	{
		TreeLocation.Y += 150.0f;
	}
	else {
		TreeLocation.Y -= 150.0f;

	}
	// drop(spawn) apple at the location
	GetWorld()->SpawnActor<ABaseApple>(SpawnObj, TreeLocation, TreeRotation);
	/*AppleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMeshComponent"));
	TreeMeshComponent = AppleMeshComponent*/

}

