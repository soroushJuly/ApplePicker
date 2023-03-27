// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScript.generated.h"

/**
 *
 */
UCLASS()
class APPLEPICKER_API ABaseLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	ABaseLevelScript();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Setup")
		class ACameraActor* Camera;

private:
		class APlayerController* Controller;

};
