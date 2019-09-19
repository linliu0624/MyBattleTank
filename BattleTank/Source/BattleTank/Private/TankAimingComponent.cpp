// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  // ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay() {
  Super::BeginPlay();

  // ...
}

// Called every frame
void UTankAimingComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed) {
  if (!barrel)
    return;
  FVector outLaunchVelocity(0);
  FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
  bool isHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
      this, outLaunchVelocity, startLocation, hitLocation, launchSpeed, false,
      0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace,
      FCollisionResponseParams());

  if (isHaveAimSolution) {
    auto aimDirection = outLaunchVelocity.GetSafeNormal();
    // FString tankName = GetOwner()->GetName();
    // UE_LOG(LogTemp, Warning, TEXT("%s Firing at %s"), *tankName,
    //        *aimDirection.ToString());
    MoveBarrelTowards(aimDirection);
  } else {
    float timeSecond = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f: No hit solution"), timeSecond);
  }
}

void UTankAimingComponent::SetBarrelRefrence(UTankBarrel *barrelToSet) {
  barrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection) {
  FRotator barrelRotation = barrel->GetForwardVector().Rotation();
  FRotator aimAsRotator = aimDirection.Rotation();
  FRotator deltaRotater = aimAsRotator - barrelRotation;

  //使砲管跟隨準星位置
  barrel->Elevate(deltaRotater.Pitch); 
}