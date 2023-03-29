// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeBase.generated.h"

//forward declare
class ABaseApple;

UCLASS()
class APPLEPICKER_API ATreeBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATreeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* TreeMeshComponent;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float OuterBoundary;
	UPROPERTY(EditAnywhere, Category = "Setup")
		float InnerBoundary;

	// Chance for the Actor to move in opposite direction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float RedirectChance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float RedirectTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float DropsInterval;

	// TSubclass is template to create UClass type safety
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
		TSubclassOf<ABaseApple> SpawnObj;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ChangeDirectionTimer;
	void ChangeDirection();
	void ChangeRandomDirection();


	FTimerHandle AppleDropsTimer;
	void DropApple();

};
