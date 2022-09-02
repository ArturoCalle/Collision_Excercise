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

	NoCollisionMaterial = CreateDefaultSubobject<UMaterial>(TEXT("No Collision Material"));
	CollisionMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Collision Material"));

	bPhysiscsEnabled = true;


}

// Called when the game starts or when spawned
void ABasicShape::BeginPlay()
{
	Super::BeginPlay();
	
	if (NoCollisionMaterial && bUseCollisionMaterials)
	{
		Mesh->SetMaterial(0, NoCollisionMaterial);
	}
	
}

// Called every frame
void ABasicShape::Tick(float DeltaTime)
{
	OverlapingActor = nullptr;
	Super::Tick(DeltaTime);

}

void ABasicShape::OnOverlapBegin(AActor* Other)
{
	OverlapingActor = Other;
}

void ABasicShape::SetCollisionMaterial()
{
	if (OverlapingActor)
	{
		if (CollisionMaterial && bUseCollisionMaterials)
		{
			Mesh->SetMaterial(0, CollisionMaterial);
		}
	}
	else
	{
		if (NoCollisionMaterial && bUseCollisionMaterials)
		{
			Mesh->SetMaterial(0, NoCollisionMaterial);
		}
	}
	
}

