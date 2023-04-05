// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BaseAppleTreeParent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseApple.generated.h"

UCLASS()
class APPLEPICKER_API ABaseApple : public ABaseAppleTreeParent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseApple();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, Category = "components")
		UStaticMeshComponent* AppleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle Effects")
		class UNiagaraSystem* AppleDestroyedParticles;



	UPROPERTY(EditAnywhere, Category = "setup")
		float LowerBound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AApplePickerGameModeBase* CurrentGameMode;

};
