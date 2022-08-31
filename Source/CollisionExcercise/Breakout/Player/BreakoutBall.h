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

	UPROPERTY(Transient)
	int32 PowerUpDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float DefaultMinVelocity;

	UPROPERTY(Transient)
	float MinVelocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float DefaultMaxVelocity;

	UPROPERTY(Transient)
	float MaxVelocity;

	UPROPERTY(Transient)
	float DefaultRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ball BP")
	TSubclassOf<ABreakoutBall> Ball_BP;
		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Kill();
	void SetPlayerReference(class ABreakoutPlayerCharacter* Player);
	void SplitBall();
};
