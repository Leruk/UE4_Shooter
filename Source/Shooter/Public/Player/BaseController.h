// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseController.generated.h"

class URespawnComponent;

UCLASS()
class SHOOTER_API ABaseController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ABaseController();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URespawnComponent* RespawnComponent;
};
