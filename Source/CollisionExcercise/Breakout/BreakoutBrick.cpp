// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBrick.h"
#include "Player/BreakoutBall.h"
#include "BreakoutGameStateBase.h"

void ABreakoutBrick::BeginPlay() 
{
	Super::BeginPlay();
	ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->AmountOfBricks++;
	}
	HitPoints = 3;
}

void ABreakoutBrick::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}
void ABreakoutBrick::OnOverlapBegin(AActor* Other)
{
	Super::OnOverlapBegin(Other);
	ABreakoutBall* Ball = Cast<ABreakoutBall>(Other);
	if (Ball)
	{
		HitBrick();
	}
}
void ABreakoutBrick::HitBrick()
{
	HitPoints--;
	if (HitPoints <= 0.0)
	{
		ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
		if (GameState)
		{
			GameState->AmountOfBricks--;
		}
		Destroy();
	}
}