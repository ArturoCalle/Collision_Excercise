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

	ShouldDebug = false;

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
					Square->MoveSquare(1.0);	
					
				}
				else if (Sphere)
				{
					Square = Cast<ASquareShape>(Object2);
					Line = Cast<ALineShape>(Object2);
					if (Square)
					{
						EvaluateCollisions(Sphere, Square, DeltaTime);
						Square->MoveSquare(1.0);
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
		UPhysicsLibrary::SolveCollision(Sphere, Sphere2);
		Sphere->OnOverlapBegin(Sphere2);
		Sphere2->OnOverlapBegin(Sphere);
	}
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, ALineShape* Line, float DeltaTime)
{
	FVector ContactPoint;
	float MovementAmount = UPhysicsLibrary::SweepLineTest(Sphere,Line, &ContactPoint,DeltaTime);
	if (MovementAmount < 1.0)
	{
		UPhysicsLibrary::SolveCollision(Sphere, Line);
		Sphere->MoveSphere(MovementAmount);
		Sphere->OnOverlapBegin(Line);
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
	
	if (ShouldDebug)
	{
		PrintDebug(Sphere, Square);
	}
	if (MovementAmount < 1.0)
	{
		
		Sphere->bIsColliding = true;
		FVector EdgeCollision = Square->CollidingWithEdge(Sphere->GetActorLocation(), Sphere->Radius);
		if (EdgeCollision != Sphere->GetActorLocation())
		{
			UPhysicsLibrary::SolveCollisionSquareEdge(Sphere, Square, ContactPoint);
			Sphere->OnOverlapBegin(Square);
			Square->OnOverlapBegin(Sphere);
		}
		else
		{
			UPhysicsLibrary::SolveCollision(Sphere, Square, ContactPoint );
			Sphere->OnOverlapBegin(Square);
			Square->OnOverlapBegin(Sphere);
		}

	}
	Sphere->MoveSphere(MovementAmount);
}

void APhysicsEngine::PrintDebug(ASphereShape* Sphere, ASquareShape* Square)
{
	//UE_LOG(LogTemp, Warning, TEXT("Square Location: %s"), *Square->GetActorLocation().ToString());
	//DrawDebugSphere(GetWorld(), Sphere->GetActorLocation(),50.0f, 20, FColor::White, false, DeltaTime * 2, 2.0);
	//MovementAmount < 1.0
	//UPhysicsLibrary::CalculateCollision(Sphere->GetActorLocation(), Sphere->Radius, Square)
	//UE_LOG(LogTemp, Warning, TEXT("Amount of movement"));
	//DrawDebugLine(GetWorld(), Sphere->GetActorLocation(), Square->GetActorLocation(), FColor::White, false, DeltaTime * 2, 2.0);
	if (UPhysicsLibrary::CalculateCollision(Sphere->GetActorLocation(), Sphere->Radius, Square))
	{
		DrawDebugSphere(GetWorld(), Sphere->GetActorLocation(), Sphere->Radius / Sphere->DefaultScale, 20, FColor::Red, false, 1.0, 1.0);
		DrawDebugBox(GetWorld(), Square->GetActorLocation(), FVector(Square->HorizontalSize, Square->VerticalSize, 10.0), FColor::Red, false, 1.0, 1.0);
	}
	
	else
	{
		DrawDebugSphere(GetWorld(), Sphere->GetActorLocation(),Sphere->Radius/ Sphere->DefaultScale, 20, FColor::White, false, 0.1, 2.0);
		DrawDebugBox(GetWorld(),Square->GetActorLocation(),FVector(Square->HorizontalSize, Square->VerticalSize, 10.0),FColor::White, false, 0.5,2.0);
	}
	
}