// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ShootAIPerceptionComponent.h"
#include "AIController.h"
#include "ShootUtils.h"
#include "Perception/AISense_Sight.h"
#include "Components/HealthComponent.h"

AActor* UShootAIPerceptionComponent::GetClosestEnemy() const {
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (auto PercieveActor : PercieveActors) {
		const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PercieveActor);
		if (HealthComponent && !HealthComponent->IsDead()) {
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance) {
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}
	return BestPawn;
}