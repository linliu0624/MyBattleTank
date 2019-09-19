// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

class ATank;
/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API ATankAIController : public AAIController {
  GENERATED_BODY()
public:
  virtual void BeginPlay() override;
  virtual void Tick(float deltaTime) override;
  ATank *GetControlledTank() const;
  ATank *GetPlayerTank() const;
};
