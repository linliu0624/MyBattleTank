// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/DrawDebugHelpers.h"
#include "Tank.h"

#define OUT

void ATankPlayerController::BeginPlay() {
  Super::BeginPlay();
  auto controlledTank = GetControlledTank();
  if (!controlledTank) {
    UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
  } else {
    UE_LOG(LogTemp, Warning, TEXT("Player controller possessing: %s"),
           *controlledTank->GetName());
  }
}

void ATankPlayerController::Tick(float deltaTime) {
  Super::Tick(deltaTime);
  // UE_LOG(LogTemp, Warning, TEXT("Player Controller tick working."))
  AimTowardsCrosshair();
}
ATank *ATankPlayerController::GetControlledTank() const {
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
  if (!GetControlledTank()) {
    return;
  }

  FVector hitLocation; // out parameter

  if (GetSightRayHitLocation(hitLocation)) {
    GetControlledTank()->AimAt(hitLocation);
    // UE_LOG(LogTemp, Warning, TEXT("hitLocation: %s"),
    // *hitLocation.ToString());
  }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &hitLocation) const {
  int32 viewPortSizeX, viewPortSizeY;
  GetViewportSize(OUT viewPortSizeX, OUT viewPortSizeY);
  auto screenLocation = FVector2D(viewPortSizeX * crossHairXLocation,
                                  viewPortSizeY * crossHairYLocation);

  FVector lookDirection;
  if (GetLookDirection(screenLocation, lookDirection)) {
    GetLookVectorHitLocation(lookDirection, hitLocation);
    // UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"),
    //       *lookDirection.ToString());
  }
  return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(
    FVector lookDirection, FVector &hitLocation) const {
  FHitResult hitResult;
  auto startLocation = PlayerCameraManager->GetCameraLocation();
  auto endLocation = startLocation + (lookDirection * lineTraceRange);
  FCollisionQueryParams Params(NAME_None, false, GetPawn()); //用來無視自己

  if (GetWorld()->LineTraceSingleByChannel(
          OUT hitResult, startLocation, endLocation,
          ECollisionChannel::ECC_Visibility, Params)) {
    hitLocation = hitResult.Location;
    return true;
  }
  hitLocation = FVector(0);
  return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation,
                                             FVector &lookDirection) const {
  FVector camaraWorldLocation;

  return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y,
                                        OUT camaraWorldLocation,
                                        OUT lookDirection);
}