// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "math.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
 void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	 Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	/*FString OurTankName = GetOwner()->GetName(); //get tank name (Actor->GetName)
	FString BarrelLocation = Barrel->GetComponentLocation().ToString(); //Get component location (SceneComponent->GetComponentLocation)
	*/
	if (!Barrel || !Turret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrel or Turret is null"));
		return;
	}
	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto time = GetWorld()->GetTimeSeconds();
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, WorldSpaceAim, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f is aiming at: %s"), time, *AimDirection.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%f no aim solution"), time);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//set barrel y position to AimDirection.Y
	FRotator ForwardRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = (AimRotator - ForwardRotator);
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	
	//rotate tank 'head' to AimDirection.X, AimDirection.Z aka Yaw
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator ForwardRotator = Turret->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = (AimRotator - ForwardRotator);
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimRotator.ToString());
	if (FMath::Abs(DeltaRotator.Yaw) > 180) 
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}

}



