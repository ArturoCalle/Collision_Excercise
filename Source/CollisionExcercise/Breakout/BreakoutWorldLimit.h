// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shapes/SquareShape.h"
#include "BreakoutWorldLimit.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ABreakoutWorldLimit : public ASquareShape
{
	GENERATED_BODY()
public:
	virtual void OnOverlapBegin(AActor* Other) override;
};
