// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ABasePickup::ABasePickup()
{
 	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateRotationYaw();
}

void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationYaw, 0));
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(PlayerPawn)) {
		PickupWasTaken();

		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakeSound, PlayerPawn->GetActorLocation());
	}
}

bool ABasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ABasePickup::PickupWasTaken() {

	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(false, true);

	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickup::Respawn, RespawnTime);
}

void ABasePickup::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	GetRootComponent()->SetVisibility(true, true);

}

void ABasePickup::GenerateRotationYaw() {
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.5f, 2.0f) * Direction;
}

bool ABasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}