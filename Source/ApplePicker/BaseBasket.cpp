// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBasket.h"
#include "Components/PrimitiveComponent.h"
// because we want to reference it in this file
#include "BaseApple.h"

// Sets default values
ABaseBasket::ABaseBasket()
	:BasketSpeed(700.0f), CurrentVelocity(0.0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));

	RootComponent = Root;
	Paddle1->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseBasket::BeginPlay()
{
	Super::BeginPlay();

	// Define what to do on two objects collide
	// We must enable simulation generate hit events on the basket
	Paddle1->OnComponentHit.AddDynamic(this, &ABaseBasket::OnHit);

}

void ABaseBasket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalPulse, const FHitResult& Hit)
{
	// To check if the other actor is of type ABaseApple
	ABaseApple* CollidedApple = Cast<ABaseApple>(OtherActor);

	if (CollidedApple)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void ABaseBasket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ABaseBasket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseBasket::MoveRight);

}

void ABaseBasket::MoveRight(float AxisValue)
{
	// CurrentVelocity.Y = AxisValue * BasketSpeed;
	// Using Clamp function to stop double calculating A and Left/ D and Right
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * BasketSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *CurrentVelocity.ToString());
}

