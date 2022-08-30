// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BreakoutGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ABreakoutGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bricks")
	int32 AmountOfBricks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Balls")
	int32 AmountOfBalls;

	void ModifyBallAmount(int32 Amount);
};
