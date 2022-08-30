// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutGameStateBase.h"
#include "BreakoutPlayerController.h"
#include "Player/BreakoutPlayerCharacter.h"

void ABreakoutGameStateBase::ModifyBallAmount(int32 Amount)
{
	AmountOfBalls += Amount;
	if (AmountOfBalls <= 0)
	{
		ABreakoutPlayerController* PlayerController = Cast<ABreakoutPlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			PlayerController->PlayerCharacter->SpawnBall();
		}
	}
}