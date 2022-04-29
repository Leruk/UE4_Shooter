// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ShootAIController.h"
#include "AI/AICharacter.h"
#include "Components/ShootAIPerceptionComponent.h"

AShootAIController::AShootAIController()
{
	ShootAIPerceptionComponent = CreateDefaultSubobject<UShootAIPerceptionComponent>("AIPerceptionComponent");
	SetPerceptionComponent(*ShootAIPerceptionComponent);
}

void AShootAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<AAICharacter>(InPawn);

	if (AICharacter) {
		RunBehaviorTree(AICharacter->BehaviorTree);
	}
}

void AShootAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = ShootAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}
