// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutGameStateBase.h"
#include "BreakoutPlayerController.h"

void ABreakoutGameStateBase::ModifyBallAmount(int32 Amount)
{
	AmountOfBalls += Amount;
	if (AmountOfBalls <= 0)
	{
		ABreakoutPlayerController* PlayerController = Cast<ABreakoutPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			DecreasePlayerLives();
			PlayerController->RespawnBall();
		}
	}
}
void ABreakoutGameStateBase::ModifyBrickAmount(int32 Amount)
{
	AmountOfBricks += Amount;
	if (AmountOfBricks <= 0)
	{
		ABreakoutPlayerController* PlayerController = Cast<ABreakoutPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			PlayerController->EndGame();
		}
	}
}
void ABreakoutGameStateBase::DecreasePlayerLives()
{
	PlayerLives--;
	if (PlayerLives <= 0)
	{
		ABreakoutPlayerController* PlayerController = Cast<ABreakoutPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			PlayerController->EndGame();
		}
		
	}
}
