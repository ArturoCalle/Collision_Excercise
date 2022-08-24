// Fill out your copyright notice in the Description page of Project Settings.


#include "Shapes/BasicShape.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"


// Sets default values
ABasicShape::ABasicShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	CollisionMaterial = CreateDefaultSubobject<UMaterial>(TEXT("CollisionMaterials"));

	NoCollisionMaterial = CreateDefaultSubobject<UMaterial>(TEXT("NoCollisionMaterial"));

}

// Called when the game starts or when spawned
void ABasicShape::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMaterial(0, NoCollisionMaterial);
	
}

// Called every frame
void ABasicShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABasicShape::SetColliding(bool bIsColliding)
{
	if (bIsColliding)
	{
		Mesh->SetMaterial(0, CollisionMaterial);

	}
	else
	{
		Mesh->SetMaterial(0, NoCollisionMaterial);
	}
}

