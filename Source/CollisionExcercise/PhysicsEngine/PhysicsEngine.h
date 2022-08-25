// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine.generated.h"

UCLASS()
class COLLISIONEXCERCISE_API APhysicsEngine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsEngine();

	UPROPERTY(Transient)
	float LoadCounter = 4;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CheckCollisions(float DeltaTime);

	void EvaluateCollisions(class ASphereShape* Sphere,  ASphereShape* Sphere2, float DeltaTime);
	void EvaluateCollisions(ASphereShape* Sphere, class ALineShape* Line, float DeltaTime);
	void EvaluateCollisions(ASphereShape* Sphere, class ASquareShape* Square, float DeltaTime);
};
