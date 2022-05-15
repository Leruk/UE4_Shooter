// Fill out your copyright notice in the Description page of Project Settings.

#include "Menu/MenuHUD.h"
#include "UI/BaseWidget.h"

void AMenuHUD::BeginPlay() 
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UBaseWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->Show();
		}
	}
}