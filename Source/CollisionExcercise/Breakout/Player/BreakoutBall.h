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
	UPROPERTY(Transient)
	TObjectPtr<class ABreakoutPlayerCharacter> Player;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Kill();
	void SetPlayerReference(class ABreakoutPlayerCharacter* Player);
};
