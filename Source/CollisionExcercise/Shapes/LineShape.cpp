// Fill out your copyright notice in the Description page of Project Settings.


#include "Shapes/LineShape.h"
#include "DrawDebugHelpers.h"

void ALineShape::BeginPlay()
{
	if (Mesh)
	{
		float HorizontalScale = (EndPoint.X - StartPoint.X)/255;
		float VerticalScale = (EndPoint.Y - StartPoint.Y)/255;

		FVector LeftSide = GetStartGlobalPosition();
		FVector RightSide = GetEndGlobalPosition();
		
		Mesh->SetRelativeScale3D(FVector(HorizontalScale, VerticalScale, 1));
	}
}

void ALineShape::Tick(float DeltaTime)
{

}
FVector ALineShape::GetStartGlobalPosition()
{
	return GetActorLocation() + StartPoint;
}
FVector ALineShape::GetEndGlobalPosition()
{
	return GetActorLocation() + EndPoint;
}
FVector ALineShape::GetLineVector()
{
	return GetStartGlobalPosition() - GetEndGlobalPosition();
}
FVector ALineShape::GetProyectionOverLine(FVector Other)
{
	FVector Proyection = GetStartGlobalPosition();
	if ((StartPoint.X - EndPoint.X) == 0)
	{
		//Is vertical line
		Proyection.Y = Other.Y;

	}
	else
	{
		// Is horizontal line
		Proyection.X = Other.X;
	}
	return Proyection;
}

bool ALineShape::IsHorizontal()
{
	if ((StartPoint.X - EndPoint.X) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}