// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AICharacter.h"
#include "AI/ShootAIController.h"
#include "Components/AIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthBarWidget.h"
#include "Components/HealthComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjInit) 
	: Super(ObjInit.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AShootAIController::StaticClass();

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthWidgetComponent->SetDrawAtDesiredSize(true);

	HealthComp->OnChangedHealth.AddUObject(this, &AAICharacter::OnHealthChanged);
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthWidgetComponent);
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateHealthWidgetVisibility();
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto AIController = Cast<AAIController>(Controller);

	if (AIController && AIController->BrainComponent) {
		AIController->BrainComponent->Cleanup();
	}
}

void AAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
	const auto HealthBarWidget = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComp->GetHealthPercent());
}

void AAICharacter::UpdateHealthWidgetVisibility()
{
	if (!GetWorld() || !GetWorld()->GetFirstLocalPlayerFromController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;

	const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
	const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
	HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}