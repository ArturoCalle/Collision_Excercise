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

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Velocity")
	FVector Velocity;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Velocity")
	FVector Acceleration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Physics")
	bool bPhysiscsEnabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
	bool bUseCollisionMaterials;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
	class UMaterial* CollisionMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Materials")
	class UMaterial* NoCollisionMaterial;

	UPROPERTY(Transient)
	AActor* OverlapingActor;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnOverlapBegin(AActor* Other);
	
	void SetCollisionMaterial();
};
