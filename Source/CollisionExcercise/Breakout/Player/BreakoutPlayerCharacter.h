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

	UPROPERTY(Transient)
	float MovementSpeed = 800;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Paddle")
	TSubclassOf<class ASquareShape> SquareShapeBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle")
	TObjectPtr<ASquareShape> Paddle;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveRight(float Value);

};
