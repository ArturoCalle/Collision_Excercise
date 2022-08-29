// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsEngine/PhysicsEngine.h"
#include "Kismet/GameplayStatics.h"
#include "Shapes/SphereShape.h"
#include "Shapes/LineShape.h"
#include "Shapes/SquareShape.h"
#include "Shapes/BasicShape.h"
#include "PhysicsLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
APhysicsEngine::APhysicsEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APhysicsEngine::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APhysicsEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (LoadCounter <= 0)
	{
		CheckCollisions(DeltaTime);
	}
	else
	{
		LoadCounter--;
	}

}
void APhysicsEngine::CheckCollisions(float DeltaTime)
{
	TArray<AActor*> SceneObjects;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicShape::StaticClass(), SceneObjects);

	for (int i = 0; i < SceneObjects.Num(); i++)
	{
		for (int j = i+1; j < SceneObjects.Num(); j++)
		{
			AActor* Object1 = SceneObjects[i];
			AActor* Object2 = SceneObjects[j];
			if (Object1 != Object2)
			{	
				ALineShape* Line;
				ASquareShape* Square;
				ASphereShape* Sphere;

				Line = Cast<ALineShape>(Object1);
				Square = Cast<ASquareShape>(Object1);
				Sphere = Cast<ASphereShape>(Object1);
				if (Line)
				{
					Sphere = Cast<ASphereShape>(Object2);
					if (Sphere)
					{
						EvaluateCollisions(Sphere, Line, DeltaTime);
					}
				}
				else if (Square)
				{
					Sphere = Cast<ASphereShape>(Object2);
					if(Sphere)
					{
						EvaluateCollisions(Sphere, Square, DeltaTime);
					}
				}
				else if (Sphere)
				{
					Square = Cast<ASquareShape>(Object2);
					Line = Cast<ALineShape>(Object2);
					if (Square)
					{
						EvaluateCollisions(Sphere, Square, DeltaTime);
					}
					else if (Line)
					{
						EvaluateCollisions(Sphere, Line, DeltaTime);			
					}
					else if(ASphereShape * Sphere2 = Cast<ASphereShape>(Object2))
					{
						EvaluateCollisions(Sphere, Sphere2, DeltaTime);
					}
					
				}
				
			}

		}
		
	}
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, ASphereShape* Sphere2, float DeltaTime)
{
	float MovementAmount = 1.0;
	FVector ContactPoint;
	if (Sphere->Velocity.SizeSquared() != 0.0)
	{
		MovementAmount = UPhysicsLibrary::SweepSphereTest(Sphere, Sphere2, &ContactPoint, DeltaTime);
	}
	else if (Sphere2->Velocity.SizeSquared() != 0.0)
	{
		MovementAmount = UPhysicsLibrary::SweepSphereTest(Sphere2, Sphere, &ContactPoint, DeltaTime);
	}
	Sphere->MoveSphere(MovementAmount);
	Sphere2->MoveSphere(MovementAmount);
	if ((MovementAmount < 1.0f))
	{	
		UE_LOG(LogTemp, Warning, TEXT("Move Amount: %f"), MovementAmount);
		UPhysicsLibrary::SolveCollision(Sphere, Sphere2);
	}
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, ALineShape* Line, float DeltaTime)
{
	FVector ContactPoint;
	float MovementAmount = UPhysicsLibrary::SweepLineTest(Sphere,Line, &ContactPoint,DeltaTime);
	if (MovementAmount < 1.0)
	{
		Sphere->bIsColliding = true;

		UPhysicsLibrary::SolveCollision(Sphere, Line);
		Sphere->MoveSphere(MovementAmount);
	}
	else
	{
		Sphere->MoveSphere(MovementAmount);
	}
	
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, class ASquareShape* Square, float DeltaTime)
{

	FVector ContactPoint;
	float MovementAmount = UPhysicsLibrary::SweepSquareTest(Sphere, Square, &ContactPoint, DeltaTime, GetWorld());
	//
	//UPhysicsLibrary::CalculateCollision(Sphere->GetActorLocation(), Sphere->Radius, Square)
	if (MovementAmount < 1.0)
	{

		Sphere->bIsColliding = true;
		FVector EdgeCollision = Square->CollidingWithEdge(Sphere->GetActorLocation(), Sphere->Radius);
		if (EdgeCollision != Sphere->GetActorLocation())
		{
			UPhysicsLibrary::SolveCollisionSquareEdge(Sphere, Square, ContactPoint);
		}
		else
		{
			UPhysicsLibrary::SolveCollision(Sphere, Square, ContactPoint );
		}

	}
	//Sphere->MoveSphere(1.0);
	Sphere->MoveSphere(MovementAmount);
}