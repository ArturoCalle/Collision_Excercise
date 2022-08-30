// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shapes/SphereShape.h"
#include "BreakoutBall.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ABreakoutBall : public ASphereShape
{
	GENERATED_BODY()

public:
	void Kill();
	void SetPlayerReference(class BreakoutPlayerCharacter* Player);
};
