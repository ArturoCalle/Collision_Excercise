// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBall.h"
#include "BreakoutPlayerCharacter.h"
#include "../BreakoutGameStateBase.h"
#include "Materials/Material.h"

void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();

}

void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float VelocitySize = Velocity.Size();
	if (VelocitySize < 70)
	{
		float multiplier = 70 / VelocitySize;
		Velocity = Velocity * multiplier;
	}
	else if (VelocitySize > 150)
	{
		float multiplier = 150 / VelocitySize;
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