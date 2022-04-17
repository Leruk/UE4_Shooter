// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"
#include "Blueprint/UserWidget.h"

void AGameHUD::BeginPlay() {
	Super::BeginPlay();

	const auto PlayerWidget = CreateWidget(GetWorld(), PlayerWidgetClass);
	PlayerWidget->AddToViewport();
	
}