// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shapes/BasicShape.h"
#include "SquareShape.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ASquareShape : public ABasicShape
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Line Data")
	FVector VerticalSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Line Data")
	FVector HorizontalSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
