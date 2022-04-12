// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHair.h"
#include "Engine/Canvas.h"

void ACrossHair::DrawHUD() {
	
	DrawCrossHair();

}

void ACrossHair::DrawCrossHair() {

	int ScaleX = Canvas->SizeX/2;
	int ScaleY = Canvas->SizeY/2;

	float HalfScale = 5.0f;

	DrawLine(ScaleX - HalfScale, ScaleY, ScaleX + HalfScale, ScaleY, FLinearColor::Green, 1.0f);
	DrawLine(ScaleX, ScaleY - HalfScale, ScaleX, ScaleY + HalfScale, FLinearColor::Green, 1.0f);
}