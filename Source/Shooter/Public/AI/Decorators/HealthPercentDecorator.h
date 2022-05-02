// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "HealthPercentDecorator.generated.h"

class ABaseWeapon;

UCLASS()
class SHOOTER_API UHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	UHealthPercentDecorator();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float HealthPercent = 0.9f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<ABaseWeapon> WeaponType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	

};
