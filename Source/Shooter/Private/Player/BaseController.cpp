// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseController.h"
#include "Components/RespawnComponent.h"

ABaseController::ABaseController()
{
	RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}