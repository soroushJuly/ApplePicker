// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelScript.h"
#include "Camera/CameraActor.h"

ABaseLevelScript::ABaseLevelScript():
Camera(nullptr), Controller(nullptr)
{
}

void ABaseLevelScript::BeginPlay()
{
	Super::BeginPlay();

	Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		Controller->SetViewTarget(Camera);
	}
}
