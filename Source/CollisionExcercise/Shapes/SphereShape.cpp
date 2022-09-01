// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereShape.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Misc/App.h"

// Sets default values
ASphereShape::ASphereShape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASphereShape::BeginPlay()
{
	DefaultScale = Radius / 50;
	SetBoundaries();
	Super::BeginPlay();
	
}

// Called every frame
void ASphereShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASphereShape::MoveSphere(float AmountOfMovement)
{
	float DeltaTime = FApp::GetDeltaTime();
	SetActorLocation(GetActorLocation() + (Velocity * DeltaTime * AmountOfMovement));
}
void ASphereShape::OnOverlapBegin(AActor* Other)
{
	Super::OnOverlapBegin(Other);
}
void ASphereShape::SetBoundaries()
{
	 float Scale = Radius / 50;

	Mesh->SetRelativeScale3D(FVector(Scale, Scale, Scale));
}
