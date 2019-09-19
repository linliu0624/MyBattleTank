// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
class ATank;
/**
 *
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
  GENERATED_BODY()
public:
  virtual void BeginPlay() override;
  virtual void Tick(float deltaTiem) override;

private:
  // Start the tank moving the barrel so that a shot would it where
  // the crosshair intersects the world
  void AimTowardsCrosshair();
  ATank *GetControlledTank() const;
  bool GetSightRayHitLocation(FVector &) const;
  bool GetLookDirection(FVector2D, FVector &) const;
  bool GetLookVectorHitLocation(FVector, FVector &) const;

  UPROPERTY(EditAnywhere)
  float crossHairXLocation = 0.5f;
  UPROPERTY(EditAnywhere)
  float crossHairYLocation = 0.3333f;
  UPROPERTY(EditAnywhere)
  float lineTraceRange = 1000000.0f; // 1是1公分,所以這樣是10公里
};
