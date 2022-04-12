// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CrossHair.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API ACrossHair : public AHUD
{
	GENERATED_BODY()

	void DrawHUD();

private:

	void DrawCrossHair();
	
};
