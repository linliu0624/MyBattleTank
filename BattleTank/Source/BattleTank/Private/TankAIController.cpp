// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
  Super::BeginPlay();

  auto controlledTank = GetControlledTank();
  if (!controlledTank) {
    UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessing a tank."));
  } else {
    UE_LOG(LogTemp, Warning, TEXT("AI controller possessing: %s"),
           *controlledTank->GetName());
  }

  auto playerTank = GetPlayerTank();
  if (!playerTank) {
    UE_LOG(LogTemp, Warning, TEXT("Do not get player tank."));
  } else {
    UE_LOG(LogTemp, Warning, TEXT("Already get player tank %s."),
           *playerTank->GetName());
  }
}

void ATankAIController::Tick(float deltaTime) {
  Super::Tick(deltaTime);
  if (GetPlayerTank()) {
    auto thisAIName = GetControlledTank()->GetName();
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
  }
  // UE_LOG(LogTemp, Warning, TEXT("AI Controller Tick() working."));
  //
}

ATank *ATankAIController::GetControlledTank() const {
  return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const {
  auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  if (!playerPawn) {
    return nullptr;
  }
  return Cast<ATank>(playerPawn);
}