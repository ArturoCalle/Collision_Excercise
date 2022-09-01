// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BreakoutPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class COLLISIONEXCERCISE_API ABreakoutPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	class ABreakoutPlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Physics")
	class APhysicsEngine* PhysicsEngine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
	class ABreakoutGameStateBase* GameState;

	UPROPERTY(Transient)
	bool CanSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Boundaries")
	float LeftLimit;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Boundaries")
	float RightLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Boundaries")
	float TopLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game End")
	bool bHasGameEnded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game End")
	TSubclassOf<class UUserWidget> WGameEnd_BP;

	UPROPERTY(Transient)
	UUserWidget* WGameEnd;

	UPROPERTY(Transient)
	float ResetLevelTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Live Counter")
	TSubclassOf<class UUserWidget> WBallCounter_BP;

	UPROPERTY(Transient)
	UUserWidget* WBallCounter;





protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent()override;
	virtual void Tick(float Deltatime)override;

	void SetUpPlayerController();

	void MoveRight(float Value);
	void Shoot();
	void ActivateDebug();
	void DeactivateDebug();
	void EndGame();
	void RespawnBall();
	
};
