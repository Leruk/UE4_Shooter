// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/ChangeWeaponService.h"
#include "AIController.h"
#include "ShootUtils.h"
#include "Components/AIWeaponComponent.h"

UChangeWeaponService::UChangeWeaponService()
{
	NodeName = "ChangeWeapon";
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();

	if (Controller) {
		const auto WeaponComponent = Utils::GetPlayerComponent<UAIWeaponComponent>(Controller->GetPawn());
		if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability) {
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
