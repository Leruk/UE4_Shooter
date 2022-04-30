// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/BaseCharacter.h"
#include "AICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTER_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:

	AAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		UBehaviorTree* BehaviorTree;

protected:

	virtual void OnDeath() override;
};
