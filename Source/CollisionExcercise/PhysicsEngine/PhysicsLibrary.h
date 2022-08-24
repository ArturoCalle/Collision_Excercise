// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PhysicsLibrary.generated.h"

UCLASS()
class COLLISIONEXCERCISE_API UPhysicsLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	static bool CalculateCollision(class ASphereShape* Sphere1, ASphereShape* Sphere2);
	static bool CalculateCollision(FVector SpherePosition, float SphereRadius, class ALineShape* Line);

	static void SolveCollision( ASphereShape* Sphere1, ASphereShape* Sphere2);
	static void SolveCollision( ASphereShape* Sphere, ALineShape* Line);

	static float SweepSphereTest( ASphereShape* DynamicSphere, ASphereShape* StaticSphere, FVector* ContactPoint, float DesiredDelta);
	static float SweepLineTest(ASphereShape* DynamicSphere, ALineShape* Line, FVector* ContactPoint, float DesiredDelta, UWorld* WorldContext);

};
