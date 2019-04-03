// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	/*FString OurTankName = GetOwner()->GetName(); //get tank name (Actor->GetName)
	FString BarrelLocation = Barrel->GetComponentLocation().ToString(); //Get component location (SceneComponent->GetComponentLocation)
	*/
	if (!Barrel)
	{
		return;
	}
	FVector OutLaunchVelocity = FVector(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, WorldSpaceAim, LaunchSpeed))
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		//Move the barrel

		UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s"), *GetOwner()->GetName(), *AimDirection.ToString());
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	//set barrel y position to AimDirection.Y
	//rotate tank 'head' to AimDirection.X, AimDirection.Z aka Yaw & Azimoth
}


