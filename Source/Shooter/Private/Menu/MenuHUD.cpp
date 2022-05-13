// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/MenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay() 
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}
}