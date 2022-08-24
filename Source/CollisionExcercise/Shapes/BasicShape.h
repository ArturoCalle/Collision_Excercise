// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicShape.generated.h"

UCLASS()
class COLLISIONEXCERCISE_API ABasicShape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicShape();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sphere Data")
	FVector Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UMaterial* CollisionMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Collision)
	class UMaterial* NoCollisionMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetColliding(bool bIsColliding);

};
