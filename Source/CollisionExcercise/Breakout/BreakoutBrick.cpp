// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBrick.h"
#include "Player/BreakoutBall.h"
#include "Player/BreakoutPlayerCharacter.h"
#include "BreakoutGameStateBase.h"
#include "BreakoutPlayerController.h"
#include "Materials/Material.h"

void ABreakoutBrick::BeginPlay() 
{
	Super::BeginPlay();
	ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
	{
		GameState->ModifyBrickAmount(1);
	}

	float powerUpRand = FMath::RandRange(0, 10);
	if (powerUpRand < 2)
	{
		bHasPowerup = true;
	}

	if (!bHasPowerup)
	{
		Mesh->SetMaterial(0, Materials[HitPoints-1]);
	}
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
		HitBrick(Other);
	}
}
void ABreakoutBrick::HitBrick(AActor* Other)
{
	HitPoints--;
	if (HitPoints <= 0.0)
	{
		if (bHasPowerup)
		{
			ABreakoutBall* Ball = Cast<ABreakoutBall>(Other);
			if(Ball)
				ApplyPowerup(Ball);
		}
		ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
		if (GameState)
		{
			GameState->ModifyBrickAmount(-1);
		}
		Destroy();
	}
	else
	{
		if(!bHasPowerup)
			Mesh->SetMaterial(0, Materials[HitPoints - 1]);
	}
}

void ABreakoutBrick::ApplyPowerup(ABreakoutBall* Ball)
{
	int32 RandomPowerUp = (int32)FMath::RandRange(0, 4);
	ABreakoutPlayerController* PlayerController = Cast<ABreakoutPlayerController>(GetWorld()->GetFirstPlayerController());


	switch(RandomPowerUp)
	{
		case 0:
		{
			//Giant Ball
			Ball->PowerUpDuration += 2;
			Ball->Radius += Ball->Radius;
			Ball->MinVelocity -= Ball->MinVelocity / 2;
			Ball->MaxVelocity -= Ball->MaxVelocity / 2;
			Ball->SetBoundaries();
		}
			break;
		case 1:
		{
			//Tiny Ball
			Ball->PowerUpDuration += 2;
			Ball->Radius -= Ball->Radius/2;
			Ball->MinVelocity += Ball->MinVelocity;
			Ball->MaxVelocity += Ball->MaxVelocity;
			Ball->SetBoundaries();
		}
			break;
		case 2:
		{
			//MultiplierBall
			Ball->SplitBall();
		}
			break;
		case 3:
		{
			//Small Paddle
			FVector NewScale = PlayerController->PlayerCharacter->GetActorScale();
			PlayerController->PlayerCharacter->SetActorScale3D(FVector(NewScale.X, NewScale.Y * 2, NewScale.Z));
			PlayerController->PlayerCharacter->PowerUpDuration += 2;
			PlayerController->PlayerCharacter->SetBoundaries();
		}
			break;
		case 4:
		{
			//Small Paddle
			FVector NewScale = PlayerController->PlayerCharacter->GetActorScale();
			PlayerController->PlayerCharacter->SetActorScale3D(FVector(NewScale.X, NewScale.Y / 2, NewScale.Z));
			PlayerController->PlayerCharacter->PowerUpDuration += 2;
			PlayerController->PlayerCharacter->SetBoundaries();
		}
			break;
		default: 
			break;
	}
}