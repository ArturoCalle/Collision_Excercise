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
	bShowContactPoints = false;
	DebugSphereDuration = 3.0;

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
		bool bAreColliding = false;
		AActor* Object1 = SceneObjects[i];
		ABasicShape* Shape = Cast<ABasicShape>(Object1);

		for (int j = i+1; j < SceneObjects.Num(); j++)
		{
			AActor* Object2 = SceneObjects[j];
			ABasicShape* Shape2 = Cast<ABasicShape>(Object2);

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
						EvaluateCollisions(Sphere, Line, DeltaTime, &bAreColliding);
					}
				}
				else if (Square)
				{
					Sphere = Cast<ASphereShape>(Object2);
					if(Sphere)
					{
						EvaluateCollisions(Sphere, Square, DeltaTime, &bAreColliding);
					}
					Square->MoveSquare(1.0);	
					
				}
				else if (Sphere)
				{
					Square = Cast<ASquareShape>(Object2);
					Line = Cast<ALineShape>(Object2);
					if (Square)
					{
						EvaluateCollisions(Sphere, Square, DeltaTime, &bAreColliding);
						Square->MoveSquare(1.0);
					}
					else if (Line)
					{
						EvaluateCollisions(Sphere, Line, DeltaTime, &bAreColliding);
					}
					else if(ASphereShape * Sphere2 = Cast<ASphereShape>(Object2))
					{
						EvaluateCollisions(Sphere, Sphere2, DeltaTime, &bAreColliding);
					}
					
				}
				
			}
			if (Shape2)
			{
				Shape2->SetCollisionMaterial();
			}
		}
		if(Shape)
		{
			Shape->SetCollisionMaterial();
		}
		
	}
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, ASphereShape* Sphere2, float DeltaTime, bool* CollisionCheck)
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
	if ((MovementAmount < 1.0f))
	{	
		*CollisionCheck = true;
		if (Sphere->bPhysiscsEnabled && Sphere2->bPhysiscsEnabled)
		{
			UPhysicsLibrary::SolveCollision(Sphere, Sphere2);
		}
		else
		{
			MovementAmount = 1.0;
		}
		Sphere->OnOverlapBegin(Sphere2);
		Sphere2->OnOverlapBegin(Sphere);
		if (bShowContactPoints)
		{
			DrawDebugSphere(GetWorld(), ContactPoint, 10.0, 20, FColor::Blue, false, DebugSphereDuration, 2.0);
		}
	}
	Sphere->MoveSphere(MovementAmount);
	Sphere2->MoveSphere(MovementAmount);
	
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, ALineShape* Line, float DeltaTime, bool* CollisionCheck)
{
	FVector ContactPoint;
	float MovementAmount = UPhysicsLibrary::SweepLineTest(Sphere,Line, &ContactPoint,DeltaTime);
	if (MovementAmount < 1.0)
	{
		*CollisionCheck = true;
		if (Sphere->bPhysiscsEnabled && Line->bPhysiscsEnabled)
		{
			UPhysicsLibrary::SolveCollision(Sphere, Line);
		}
		else
		{
			MovementAmount = 1.0;
		}
		Sphere->MoveSphere(MovementAmount);
		Sphere->OnOverlapBegin(Line);
		if (bShowContactPoints)
		{
			DrawDebugSphere(GetWorld(), ContactPoint, 10.0, 20, FColor::Red, false, DebugSphereDuration, 2.0);
		}
	}
	else
	{
		Sphere->MoveSphere(MovementAmount);
	}
	
}
void APhysicsEngine::EvaluateCollisions(ASphereShape* Sphere, class ASquareShape* Square, float DeltaTime, bool* CollisionCheck)
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
			*CollisionCheck = true;
			if (Sphere->bPhysiscsEnabled && Square->bPhysiscsEnabled)
			{
				UPhysicsLibrary::SolveCollisionSquareEdge(Sphere, Square, ContactPoint);
			}
			else
			{
				MovementAmount = 1.0;
			}
			Sphere->OnOverlapBegin(Square);
			Square->OnOverlapBegin(Sphere);
			if (bShowContactPoints)
			{
				DrawDebugSphere(GetWorld(), ContactPoint, 10.0, 20, FColor::White, false, DebugSphereDuration, 2.0);
			}
		}
		else
		{
			*CollisionCheck = true;
			if (Sphere->bPhysiscsEnabled && Square->bPhysiscsEnabled)
			{
				UPhysicsLibrary::SolveCollision(Sphere, Square, ContactPoint );
			}
			else
			{
				MovementAmount = 1.0;
			}
			Sphere->OnOverlapBegin(Square);
			Square->OnOverlapBegin(Sphere);
			if (bShowContactPoints)
			{
				DrawDebugSphere(GetWorld(), ContactPoint, 10.0, 20, FColor::White, false, DebugSphereDuration, 2.0);
			}
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