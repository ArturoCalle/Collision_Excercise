// Fill out your copyright notice in the Description page of Project Settings.


#include "Shapes/SquareShape.h"
#include "DrawDebugHelpers.h"


void ASquareShape::BeginPlay()
{
	Super::BeginPlay();
	VerticalSize = GetActorScale().Y * 50;
	HorizontalSize = GetActorScale().X *50;

	// get positions of all corners
	TopLeftCorner = GetActorLocation();
	TopLeftCorner.Y += VerticalSize;
	TopLeftCorner.X += HorizontalSize;

	TopRightCorner = GetActorLocation();
	TopRightCorner.Y += VerticalSize;
	TopRightCorner.X -= HorizontalSize;

	BottomRightCorner = GetActorLocation();
	BottomRightCorner.Y -= VerticalSize;
	BottomRightCorner.X -= HorizontalSize;

	BottomLeftCorner = GetActorLocation();
	BottomLeftCorner.Y -= VerticalSize;
	BottomLeftCorner.X += HorizontalSize;

	DrawDebugSphere(GetWorld(), TopLeftCorner, 10.0, 20, FColor::Black, false, 2.0, 2.0);
	DrawDebugSphere(GetWorld(), TopRightCorner, 10.0, 20, FColor::White, false, 2.0, 2.0);
	DrawDebugSphere(GetWorld(), BottomLeftCorner, 10.0, 20, FColor::Red, false, 2.0, 2.0);
	DrawDebugSphere(GetWorld(), BottomRightCorner, 10.0, 20, FColor::Blue, false, 2.0, 2.0);
}

void ASquareShape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
FVector ASquareShape::GetProyectionSquare(FVector Other)
{
	FVector Proyection = GetActorLocation();

	if ((Other.Y > Proyection.Y - VerticalSize) && (Other.Y < Proyection.Y + VerticalSize))
	{
		//On horizontal range
		if (Other.X > Proyection.X)
		{
			//Left Wall
			Proyection.X = TopLeftCorner.X;
			Proyection.Y = Other.Y;
		}
		else
		{
			//Right Wall
			Proyection.X = TopRightCorner.X;
			Proyection.Y = Other.Y;
		}
	}
	else if((Other.X > Proyection.X - HorizontalSize) && (Other.X < Proyection.X + HorizontalSize))
	{
		//On vertical range
		if (Other.Y > Proyection.Y)
		{
			//Top Wall
			Proyection.Y = TopLeftCorner.Y;;
			Proyection.X = Other.X;
		}
		else
		{
			//Bottom Wall
			Proyection.Y = BottomLeftCorner.Y;
			Proyection.X = Other.X;
		}
	}

	return Proyection;
}
bool ASquareShape::CollidingWithEdge(FVector SpherePosition, float Radius)
{
	float DistanceToEdge = (TopLeftCorner - SpherePosition).Size();
	
	if (DistanceToEdge <= Radius)
		return true;

	DistanceToEdge = (TopRightCorner - SpherePosition).Size();
	if (DistanceToEdge <= Radius)
		return true;

	DistanceToEdge = (BottomLeftCorner - SpherePosition).Size();
	if (DistanceToEdge <= Radius)
		return true;

	DistanceToEdge = (BottomRightCorner - SpherePosition).Size();
	if (DistanceToEdge <= Radius)
		return true;

	return false;
}
