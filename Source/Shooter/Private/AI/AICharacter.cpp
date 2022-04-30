// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/ShootAIController.h"
#include "Components/AIWeaponComponent.h"
#include "BrainComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AShootAIController::StaticClass();
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = Cast<AAIController>(Controller);

	if (AIController && AIController->BrainComponent) {
		AIController->BrainComponent->Cleanup();
	}
}
