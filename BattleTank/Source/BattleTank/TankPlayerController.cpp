// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing any tank"));
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	AimTowardsCrosshair();

}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}
	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	FVector LookDirection;
	if (GetLookDirection(LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			GetControlledTank()->AimAt(OutHitLocation);
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector cameraPos;
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, cameraPos, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& hitLocation) const
{
	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		hitResult,
		PlayerCameraManager->GetCameraLocation(), //start location is the camera position
		PlayerCameraManager->GetCameraLocation() + (LineTraceRange * LookDirection), //then go out 10km by LookDirection
		ECC_Visibility
	))
	{
		hitLocation = hitResult.Location;
		return true;
	}
	hitLocation = FVector(0.0F);
	return false;	
}
