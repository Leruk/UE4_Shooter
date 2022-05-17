// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootGameInstance.h"
#include "Sound/SoundFuncLib.h"

void UShootGameInstance::ToggleVolume()
{
	USoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}