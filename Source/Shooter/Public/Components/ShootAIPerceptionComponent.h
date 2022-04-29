// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ShootAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UShootAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:

	AActor* GetClosestEnemy() const;
	
};
