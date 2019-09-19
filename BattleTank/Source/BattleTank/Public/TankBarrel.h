// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent {
  GENERATED_BODY()
public:
  void Elevate(float);


private:
  UPROPERTY(EditAnywhere, Category = Setup)
  float maxDegreesPerSecond = 5;

  UPROPERTY(EditAnywhere, Category = Setup)
  float maxElevationDegrees = 30;

  UPROPERTY(EditAnywhere, Category = Setup)
  float minElevationDegrees = -5;
};
