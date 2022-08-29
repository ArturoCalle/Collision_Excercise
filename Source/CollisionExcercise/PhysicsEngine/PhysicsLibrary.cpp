// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsEngine/PhysicsLibrary.h"
#include "Shapes/SphereShape.h"
#include "Shapes/SquareShape.h"
#include "Shapes/LineShape.h"
#include "Misc/App.h"
#include "DrawDebugHelpers.h"

bool UPhysicsLibrary::CalculateCollision(ASphereShape* Sphere1, ASphereShape* Sphere2)
{
	if (Sphere1 && Sphere2)
	{
		FVector Diference = Sphere1->GetActorLocation() - Sphere2->GetActorLocation();
		float Distance = Diference.Size();
		float CollisionDistance = FMath::Abs(Sphere1->Radius) + FMath::Abs(Sphere2->Radius);

		if (Distance <= CollisionDistance)
		{
			return true;
		}
	}
	return false;
}
bool UPhysicsLibrary::CalculateCollision(FVector SpherePosition, float SphereRadius, ALineShape* Line)
{
	if (Line->IsHorizontal())
	{
		//the proyection is within the line size range
		if ((SpherePosition.X > Line->GetStartGlobalPosition().X) || (SpherePosition.X < Line->GetEndGlobalPosition().X))
		{
			FVector DistanceToStart = SpherePosition - Line->GetStartGlobalPosition();
			FVector DistanceToEnd = SpherePosition - Line->GetEndGlobalPosition();
			if (DistanceToStart.Size() <= SphereRadius)
			{
				return true;
			}
			if (DistanceToEnd.Size() <= SphereRadius)
			{
				return true;
			}
			return false;
		}
	}
	else
	{
		if ((SpherePosition.Y > Line->GetStartGlobalPosition().Y) || (SpherePosition.Y < Line->GetEndGlobalPosition().Y))
		{
			FVector DistanceToStart = SpherePosition - Line->GetStartGlobalPosition();
			FVector DistanceToEnd = SpherePosition - Line->GetEndGlobalPosition();
			if (DistanceToStart.Size() <= SphereRadius)
			{
				return true;
			}
			if (DistanceToEnd.Size() <= SphereRadius)
			{
				return true;
			}
			return false;
		}
	}
	FVector Proyection = Line->GetProyectionOverLine(SpherePosition);
	FVector DistanceToProyection = SpherePosition - Proyection;
	if (DistanceToProyection.Size() <= SphereRadius)
	{
		return true;
	}
	return false;
}
bool UPhysicsLibrary::CalculateCollision(FVector SpherePosition, float SphereRadius, class ASquareShape* Square)
{	
	//calculations taken from https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
	/*
	
	FVector CircleDistance = FVector((float)FMath::Abs(SpherePosition.X - Square->GetActorLocation().X),
								  	 (float)FMath::Abs(SpherePosition.Y - Square->GetActorLocation().Y),
								     0.0f);
	if(CircleDistance.X > (Square->HorizontalSize / 2 + SphereRadius))
		return false;
	if(CircleDistance.Y > (Square->VerticalSize / 2 + SphereRadius))
		return false;
	if(CircleDistance.X <= (Square->HorizontalSize / 2 ))
		return true;
	if (CircleDistance.Y <= (Square->VerticalSize / 2))
		return true;

	float CornerDistSq = ((CircleDistance.X - Square->HorizontalSize / 2) * (CircleDistance.X - Square->HorizontalSize / 2)) + ((CircleDistance.Y - Square->VerticalSize / 2) * (CircleDistance.Y - Square->VerticalSize / 2));

	return (CornerDistSq <= (SphereRadius * SphereRadius));
	
	/*
	old collision 
	*/

	FVector EdgeCollision = Square->CollidingWithEdge(SpherePosition, SphereRadius);
	if (EdgeCollision != SpherePosition)
	{
		return true;
	}
	FVector ProyectionOnSquare = Square->GetProyectionSquare(SpherePosition);
	if (ProyectionOnSquare != Square->GetActorLocation())
	{
		float DistanceToProyection = (SpherePosition - ProyectionOnSquare).Size();
		if (DistanceToProyection <= SphereRadius)
		{
			return true;
		}
	}

	FVector CircleDistance = FVector((float)FMath::Abs(SpherePosition.X - Square->GetActorLocation().X),
									(float)FMath::Abs(SpherePosition.Y - Square->GetActorLocation().Y),
									0.0f);
	if (CircleDistance.X > (Square->HorizontalSize / 2 + SphereRadius))
		return false;
	if (CircleDistance.Y > (Square->VerticalSize / 2 + SphereRadius))
		return false;
	if (CircleDistance.X <= (Square->HorizontalSize / 2))
		return true;
	if (CircleDistance.Y <= (Square->VerticalSize / 2))
		return true;

	float CornerDistSq = ((CircleDistance.X - Square->HorizontalSize / 2) * (CircleDistance.X - Square->HorizontalSize / 2)) + ((CircleDistance.Y - Square->VerticalSize / 2) * (CircleDistance.Y - Square->VerticalSize / 2));

	return (CornerDistSq <= (SphereRadius * SphereRadius));
	//return false;
}

//call in case of collision
void UPhysicsLibrary::SolveCollision(ASphereShape* Sphere1, ASphereShape* Sphere2)
{
	if (Sphere1 && Sphere2)
	{
		//Check if Spheres are crossovelapping
		FVector Distance = Sphere1->GetActorLocation() - Sphere2->GetActorLocation();
		float DistanceMagnitude = Distance.Size();
		float RadiusSum = Sphere1->Radius + Sphere2->Radius;

		if (DistanceMagnitude < RadiusSum)
		{
			float DeltaTime = (float)FApp::GetDeltaTime();
			Sphere1->SetActorLocation(Sphere1->GetActorLocation() - (Sphere1->Velocity * DeltaTime));
			Sphere2->SetActorLocation(Sphere2->GetActorLocation() - (Sphere2->Velocity * DeltaTime));

			
			Distance = Sphere1->GetActorLocation() - Sphere2->GetActorLocation();
			DistanceMagnitude = Distance.Size();
			
		}

		/*Physics calculations taken from: https://studiofreya.com/3d-math-and-physics/simple-sphere-sphere-collision-detection-and-collision-response/
		*/

		Distance = Sphere1->GetActorLocation() - Sphere2->GetActorLocation();
		Distance.Normalize();

		//Sphere 1 velocity calculation
		FVector VelocityV1 = Sphere1->Velocity;
		float Dot1 = Distance.Dot(VelocityV1);
		FVector ResultVelocityV1X = Distance * Dot1;
		FVector ResultVelocityV1Y = VelocityV1 - ResultVelocityV1X;

		//Sphere 2 velocity calculation
		Distance = Distance * -1;
		FVector VelocityV2 = Sphere2->Velocity;
		float Dot2 = Distance.Dot(VelocityV2);
		FVector ResultVelocityV2X = Distance * Dot2;
		FVector ResultVelocityV2Y = VelocityV2 - ResultVelocityV2X;

		//Asing new velocity for result colision
		float m1 = Sphere1->Mass;
		float m2 = Sphere2->Mass;

		Sphere1->Velocity = (ResultVelocityV1X * (m1 - m2)) / (m1 + m2) + (ResultVelocityV2X * (2 * m2)) / (m1 + m2) + ResultVelocityV1Y;
		Sphere2->Velocity = (ResultVelocityV1X * (2*m1)) / (m1 + m2) + (ResultVelocityV2X * (m2-m1)) / (m1 + m2) + ResultVelocityV2Y;

		
		Sphere1->Velocity.Z = 0.0f;
		Sphere2->Velocity.Z = 0.0f;
	}
	
}

void UPhysicsLibrary::SolveCollision(ASphereShape* Sphere, ALineShape* Line)
{
	FVector Distance = Line->GetProyectionOverLine(Sphere->GetActorLocation());
	Distance.Normalize();
	if (Line->IsHorizontal())
	{
		Sphere->Velocity.Y = -Sphere->Velocity.Y;
	}
	else
	{
		Sphere->Velocity.X = -Sphere->Velocity.X;
	}
	
}
void UPhysicsLibrary::SolveCollision(ASphereShape* Sphere, ASquareShape* Square, FVector ContactPoint)
{
	if ((Sphere->GetActorLocation().Y > Square->GetActorLocation().Y - Square->VerticalSize) && (Sphere->GetActorLocation().Y < Square->GetActorLocation().Y + Square->VerticalSize))
	{
		//On horizontal range
		Sphere->Velocity.X = -Sphere->Velocity.X;
		
	}
	else //else if ((Sphere->GetActorLocation().X > Square->GetActorLocation().X - Square->HorizontalSize) && (Sphere->GetActorLocation().X < Square->GetActorLocation().X + Square->HorizontalSize))
	{
		//On vertical range
		Sphere->Velocity.Y = -Sphere->Velocity.Y;
	}
}
void UPhysicsLibrary::SolveCollisionSquareEdge(ASphereShape* Sphere, ASquareShape* Square, FVector ContactPoint)
{
	FVector CollisionWithEdge = Square->CollidingWithEdge(Sphere->GetActorLocation(), Sphere->Radius);
	if (Sphere->GetActorLocation() != CollisionWithEdge)
	{
		//Calculation of collision with edge from: https://stackoverflow.com/questions/49747121/sphere-to-block-corner-collision-detection-js

		float V1X = Sphere->GetActorLocation().X - CollisionWithEdge.X;
		float V1Y = Sphere->GetActorLocation().Y - CollisionWithEdge.Y;

		float Lenght = FMath::Sqrt(((V1X * V1X) + (V1Y * V1Y)));
		FVector Tangent = FVector(-V1Y / Lenght, V1X / Lenght, 0.0f);

		float DotSphereTangent = Sphere->Velocity.Dot(Tangent);

		Sphere->Velocity.X = -Sphere->Velocity.X + Tangent.X * DotSphereTangent;
		Sphere->Velocity.Y = -Sphere->Velocity.Y + Tangent.Y * DotSphereTangent;

	}
}

float UPhysicsLibrary::SweepSphereTest(ASphereShape* DynamicSphere, ASphereShape* StaticSphere, FVector* ContactPoint, float DesiredDelta)
{
	//Calculation of size vector between objective and dynamic sphere to determine the max amount of movement to make colllsion happen
	FVector Difference = DynamicSphere->GetActorLocation() - StaticSphere->GetActorLocation();

	if (DynamicSphere->Velocity.SizeSquared() == 0)
	{
		*ContactPoint = DynamicSphere->GetActorLocation();
		return 1.0;
	}

	//Simulation of movement to detarmine collision happening
	FVector SimulatedDynamicSpherePosition = DynamicSphere->GetActorLocation() + (DesiredDelta * DynamicSphere->Velocity);
	FVector SimulationVSStaticCenterDistance = SimulatedDynamicSpherePosition - StaticSphere->GetActorLocation();
	float SpheresCenterDistance = SimulationVSStaticCenterDistance.Size();
	float RadiusSum = FMath::Abs(DynamicSphere->Radius) + FMath::Abs(StaticSphere->Radius);

	if (SpheresCenterDistance <= RadiusSum)
	{

		double UnitsToMove = (DesiredDelta / 10);
		int IterationCounter = 0;

		while (SpheresCenterDistance <= RadiusSum)
		{
			IterationCounter++;	
			SimulatedDynamicSpherePosition = SimulatedDynamicSpherePosition + (UnitsToMove * -DynamicSphere->Velocity);
			SimulationVSStaticCenterDistance = SimulatedDynamicSpherePosition - StaticSphere->GetActorLocation();
			SpheresCenterDistance = SimulationVSStaticCenterDistance.Size();
		}
		*ContactPoint = SimulatedDynamicSpherePosition - (SimulationVSStaticCenterDistance * DynamicSphere->Radius);
		
		// check the portion of the desired delta that would ocur on the movement
		float TimeFromOriginToCollision = UnitsToMove * IterationCounter;

		if (TimeFromOriginToCollision < DesiredDelta)
		{
			return TimeFromOriginToCollision/DesiredDelta;
		}
		else
		{
			return DesiredDelta;
		}
	}

	*ContactPoint = SimulatedDynamicSpherePosition;
	return 1.0;
}

float UPhysicsLibrary::SweepLineTest(ASphereShape* Sphere, ALineShape* Line, FVector* ContactPoint, float DesiredDelta)
{
	FVector ProyectionSphereOnLine = Line->GetProyectionOverLine(Sphere->GetActorLocation());

	float ExpectedMovement = (DesiredDelta * Sphere->Velocity).Size()+ Sphere->Radius;
	float DistanceSphereToLine = (ProyectionSphereOnLine - Sphere->GetActorLocation()).Size();
	
	if ((Sphere->Velocity.SizeSquared() == 0)||(ExpectedMovement < DistanceSphereToLine))
	{
		*ContactPoint = Sphere->GetActorLocation();
		return 1.0;
	}

	FVector SphereProyectedPosition = Sphere->GetActorLocation() + (DesiredDelta * Sphere->Velocity);
	if (CalculateCollision(SphereProyectedPosition, Sphere->Radius, Line))
	{
		float OffsetAmount = ExpectedMovement - DistanceSphereToLine;
		float AmountOfMovement = OffsetAmount/ExpectedMovement;
		return AmountOfMovement;
	}
	
	return 1.0;
}

float UPhysicsLibrary::SweepSquareTest(ASphereShape* Sphere, ASquareShape* Square, FVector* ContactPoint, float DesiredDelta, UWorld* WorldContext)
{
	FVector SphereProyectedPosition = Sphere->GetActorLocation() + (DesiredDelta * Sphere->Velocity);
	if (!Sphere->Velocity.SizeSquared() == 0)
	{
		if (CalculateCollision(SphereProyectedPosition, Sphere->Radius, Square))
		{
			float DistanceSphereToSquare;
			float ExpectedMovement = (DesiredDelta * Sphere->Velocity).Size() + Sphere->Radius;
			FVector EdgeCollision = Square->CollidingWithEdge(SphereProyectedPosition, Sphere->Radius);
			if (SphereProyectedPosition != EdgeCollision)
			{
				DistanceSphereToSquare = (EdgeCollision - Sphere->GetActorLocation()).Size();
			}
			else
			{
				FVector ProyectionSphereOnSquare = Square->GetProyectionSquare(Sphere->GetActorLocation());
				DistanceSphereToSquare = (ProyectionSphereOnSquare - Sphere->GetActorLocation()).Size();
			}

			if (ExpectedMovement < DistanceSphereToSquare)
			{
				*ContactPoint = Sphere->GetActorLocation();
				return 1.0;
			}
			float OffsetAmount = ExpectedMovement - DistanceSphereToSquare;
			float AmountOfMovement = OffsetAmount / ExpectedMovement;
			return AmountOfMovement;
		}
	}
	*ContactPoint = Sphere->GetActorLocation();
	return 1.0;
	
}