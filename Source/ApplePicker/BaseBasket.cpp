// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBasket.h"
#include "Components/PrimitiveComponent.h"
// because we want to reference it in this file
#include "BaseApple.h"

// Sets default values
ABaseBasket::ABaseBasket()
	:BasketSpeed(700.0f), PaddlesOffset(FVector(0.0f, 0.0f, 120.0f)), CurrentVelocity(0.0)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));

	RootComponent = Root;
	Paddle1->SetupAttachment(RootComponent);
	Paddle2->SetupAttachment(Paddle1);
	Paddle3->SetupAttachment(Paddle2);

	// Programmitically set controller who posses the pawn 
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABaseBasket::BeginPlay()
{
	Super::BeginPlay();

	// Enabaling simulation generate hit event by default
	Paddle1->SetNotifyRigidBodyCollision(true);
	Paddle2->SetNotifyRigidBodyCollision(true);
	Paddle3->SetNotifyRigidBodyCollision(true);

	// Define what to do on two objects collide
	// We must enable simulation generate hit events on the basket
	Paddle1->OnComponentHit.AddDynamic(this, &ABaseBasket::OnHit);
	Paddle2->OnComponentHit.AddDynamic(this, &ABaseBasket::OnHit);
	Paddle3->OnComponentHit.AddDynamic(this, &ABaseBasket::OnHit);

}

void ABaseBasket::PreRegisterAllComponents()
{
	Super::PreRegisterAllComponents();

	// Set a relative location to the parent
	Paddle2->SetRelativeLocation(PaddlesOffset);
	Paddle3->SetRelativeLocation(PaddlesOffset);
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

