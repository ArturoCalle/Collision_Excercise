// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BreakoutPlayerCharacter.generated.h"

UCLASS()
class COLLISIONEXCERCISE_API ABreakoutPlayerCharacter : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABreakoutPlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Paddle")
	float MovementSpeed = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Paddle")
	TSubclassOf<class ASquareShape> SquareShapeBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle")
	TObjectPtr<ASquareShape> Paddle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Balls")
	TObjectPtr<class ABreakoutBall> AttachedBall;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Balls")
	TSubclassOf<ABreakoutBall> Ball_BP;

	UPROPERTY(Transient)
	TObjectPtr<class ABreakoutPlayerController> PlayerController;

	UPROPERTY(Transient)
	float SpawnCoolDown;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRight(float Value);
	void SpawnBall();
	void ShootBall();

};
