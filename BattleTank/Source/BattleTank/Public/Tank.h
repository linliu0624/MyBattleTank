// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
UCLASS()
class BATTLETANK_API ATank : public APawn {
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ATank();
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  void AimAt(FVector);

  UFUNCTION(BlueprintCallable, Category = Setup)
  void SetBarrelRefrence(UTankBarrel *barrelToSet);

protected:
  UTankAimingComponent *tankAimingComponent = nullptr;

private:
  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;
  UPROPERTY(EditAnywhere, Category = Firing)
  float launchSpeed = 4000.f;
};
