// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shapes/SquareShape.h"
#include "BreakoutBrick.generated.h"


/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ABreakoutBrick : public ASquareShape
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "HitPoints")
	int32 HitPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUP")
	bool bHasPowerup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
	TArray<class UMaterial*> Materials;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(AActor* Other) override;
	void HitBrick(AActor* Other);
	void ApplyPowerup(class ABreakoutBall* Other);
	
};
