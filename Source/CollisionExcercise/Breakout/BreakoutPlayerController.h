// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BreakoutPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ABreakoutPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class ABreakoutPlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	class APhysicsEngine* PhysicsEngine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	class ABreakoutGameStateBase* GameState;

	UPROPERTY(Transient)
	bool CanSpawn;

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent()override;
	virtual void Tick(float Deltatime)override;

	void MoveRight(float Value);
	void Shoot();
	void ActivateDebug();
	void DeactivateDebug();
	
};
