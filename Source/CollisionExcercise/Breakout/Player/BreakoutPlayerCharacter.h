// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Shapes/SquareShape.h"
#include "BreakoutPlayerCharacter.generated.h"

UCLASS()
class COLLISIONEXCERCISE_API ABreakoutPlayerCharacter : public ASquareShape
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABreakoutPlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Paddle")
	float MovementSpeed = 1000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Balls")
	TObjectPtr<class ABreakoutBall> AttachedBall;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Balls")
	TSubclassOf<ABreakoutBall> Ball_BP;

	UPROPERTY(Transient)
	TObjectPtr<class ABreakoutPlayerController> PlayerController;

	UPROPERTY(Transient)
	float SpawnCoolDown;

	UPROPERTY(Transient)
	int32 PowerUpDuration;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnOverlapBegin(AActor* Other) override;

	void MoveRight(float Value);
	void SpawnBall();
	void ShootBall();

};
