// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocationTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UNextLocationTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UNextLocationTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	float Radius = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Navigation")
	FBlackboardKeySelector AimLocationKey;
	
};
