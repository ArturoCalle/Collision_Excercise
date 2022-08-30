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
	class ABreakoutPlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class APhysicsEngine* PhysicsEngine;

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent()override;
	virtual void Tick(float Deltatime)override;

	void MoveRight(float Value);
	void ActivateDebug();
	void DeactivateDebug();
	
};
