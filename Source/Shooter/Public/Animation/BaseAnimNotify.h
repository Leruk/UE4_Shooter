// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BaseAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotify, USkeletalMeshComponent*);

UCLASS()
class SHOOTER_API UBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	FOnNotify OnNotify;

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
