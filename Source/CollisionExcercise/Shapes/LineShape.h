// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shapes/BasicShape.h"
#include "LineShape.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ALineShape : public ABasicShape
{
	GENERATED_BODY()

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Line Data")
	FVector StartPoint;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Line Data")
	FVector EndPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetStartGlobalPosition();
	FVector GetEndGlobalPosition();
	FVector GetLineVector();
	FVector GetProyectionOverLine(FVector other);
	
	bool IsHorizontal();
};
