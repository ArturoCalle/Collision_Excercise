// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBall.h"
#include "BreakoutPlayerCharacter.h"
#include "../BreakoutGameStateBase.h"

void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();
}

void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Velocity.Size() < 100)
	{

	}
	if (Velocity.Size() > 500)
	{

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