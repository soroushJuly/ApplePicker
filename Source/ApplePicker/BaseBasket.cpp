// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBasket.h"

// Sets default values
ABaseBasket::ABaseBasket()
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
	
}

// Called every frame
void ABaseBasket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseBasket::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
