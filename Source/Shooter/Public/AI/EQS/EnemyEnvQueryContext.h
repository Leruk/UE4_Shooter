// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnemyEnvQueryContext.generated.h"

UCLASS()
class SHOOTER_API UEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName EnemyActorKey = "EnemyActor";
};
