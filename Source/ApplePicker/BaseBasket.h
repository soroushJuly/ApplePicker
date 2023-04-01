// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "BaseBasket.generated.h"


UCLASS()
class APPLEPICKER_API ABaseBasket : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseBasket();

	// Function to destroy a paddle in the basket
	// This will be called from other actors soo it should be in public section
	void DestroyPaddle();

	APlayerController* GetBasketPlayerController() const;

protected:
	// Called when the game starts or when spawned
	// Begin Play is the last VIRTUAL function called in aactor 
	virtual void BeginPlay() override;

	virtual void PreRegisterAllComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
		UStaticMeshComponent* Paddle1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
		UStaticMeshComponent* Paddle2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "components")
		UStaticMeshComponent* Paddle3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		float BasketSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		FVector PaddlesOffset;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalPulse, const FHitResult& Hit);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector CurrentVelocity;

	void MoveRight(float AxisValue);

	TArray<UStaticMeshComponent*> PaddleList;

	class AApplePickerGameModeBase* GameMode;

	APlayerController* Controller;
};
