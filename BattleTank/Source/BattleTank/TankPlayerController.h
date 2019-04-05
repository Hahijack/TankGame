// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void PlayerTick(float DeltaTime) override;



private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation  ) const;

	bool GetLookDirection(FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& hitLocation) const;
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

};
