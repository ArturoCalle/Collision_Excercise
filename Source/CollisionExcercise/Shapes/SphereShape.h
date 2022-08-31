// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicShape.h"
#include "GameFramework/Actor.h"
#include "SphereShape.generated.h"

UCLASS()
class COLLISIONEXCERCISE_API ASphereShape : public ABasicShape
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereShape();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sphere Data")
	float Radius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sphere Data")
	float Mass;

	UPROPERTY(Transient)
	bool bIsColliding;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveSphere(float AmountOfMovement);
	void SetBoundaries();

	virtual void OnOverlapBegin(AActor* Other) override;
};
