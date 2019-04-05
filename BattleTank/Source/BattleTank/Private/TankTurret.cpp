// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"
#include "math.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	float ChangeInRotation = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewYaw = RelativeRotation.Yaw + ChangeInRotation;

	SetRelativeRotation(FRotator(0, NewYaw, 0));


}



