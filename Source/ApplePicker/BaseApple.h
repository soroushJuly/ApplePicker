// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseApple.generated.h"

UCLASS()
class APPLEPICKER_API ABaseApple : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "components")
		UStaticMeshComponent* AppleMeshComponent;
	UPROPERTY(EditAnywhere, Category = "setup")
		float LowerBound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
