// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBall.h"
#include "BreakoutPlayerCharacter.h"
#include "../BreakoutGameStateBase.h"

void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();

	MinVelocity = DefaultMinVelocity;
	MaxVelocity = DefaultMaxVelocity;
	DefaultRadius = Radius;

	Velocity = FVector(0.0f, 0.0f, 0.0f);

}

void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float VelocitySize = Velocity.Size();
	if (VelocitySize < MinVelocity)
	{
		float multiplier = MinVelocity / VelocitySize;
		Velocity = Velocity * multiplier;
	}
	else if (VelocitySize > MaxVelocity)
	{
		float multiplier = MaxVelocity / VelocitySize;
		Velocity = Velocity * multiplier;
	}
}

void ABreakoutBall::Kill()
{
	ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->ModifyBallAmount(-1);
	}
	Destroy();
}
void ABreakoutBall::SetPlayerReference(ABreakoutPlayerCharacter* PlayerCharacter)
{
	Player = PlayerCharacter;
}
void SplitBall()
{

}