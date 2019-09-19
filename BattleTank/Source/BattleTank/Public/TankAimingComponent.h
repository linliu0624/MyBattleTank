// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"
//前置宣告，可以讓標頭不要包含其他標頭
//讓編譯器先看到說，有這個class就對了
//雖然標頭沒有包含但是去cpp就會看到詳細內容了
class UTankBarrel;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent {
  GENERATED_BODY()

public:
  // Sets default values for this component's properties
  UTankAimingComponent();
  // Called when the game starts
  virtual void BeginPlay() override;
  // Called every frame
  virtual void
  TickComponent(float DeltaTime, ELevelTick TickType,
                FActorComponentTickFunction *ThisTickFunction) override;
  void AimAt(FVector, float);
  void SetBarrelRefrence(UTankBarrel *);
  //TODO add SetTurretRefrence
private:
  UTankBarrel *barrel = nullptr;
  void MoveBarrelTowards(FVector);
};
