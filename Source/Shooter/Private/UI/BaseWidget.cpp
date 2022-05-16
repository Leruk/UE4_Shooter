// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BaseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UBaseWidget::Show()
{
	PlayAnimation(ShowAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}