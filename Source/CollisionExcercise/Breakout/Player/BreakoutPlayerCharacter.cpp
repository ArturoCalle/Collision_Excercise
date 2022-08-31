// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/Player/BreakoutPlayerCharacter.h"
#include "BreakoutBall.h"
#include "../BreakoutGameStateBase.h"
#include "../BreakoutPlayerController.h"
#include "Misc/App.h"

// Sets default values
ABreakoutPlayerCharacter::ABreakoutPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABreakoutPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetBoundaries();
	SpawnCoolDown = 0.0;
	SpawnBall();
}

// Called every frame
void ABreakoutPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SpawnCoolDown > 0.0)
	{
		SpawnCoolDown -= DeltaTime;
	}

	if(AttachedBall)
	{
		FVector BallLocation = FVector(GetActorLocation().X + HorizontalSize + AttachedBall->Radius, GetActorLocation().Y , 0.0);
		AttachedBall->SetActorLocation(BallLocation);
	}
}

void ABreakoutPlayerCharacter::MoveRight(float Value)
{
	const FVector Direction = FVector::RightVector;
	Velocity = Direction * (MovementSpeed * Value);
}
void ABreakoutPlayerCharacter::SpawnBall()
{
	ResetPowerup();
	if (SpawnCoolDown <= 0.0)
	{
		SpawnCoolDown = 0.5;
		FVector BallSpawn = FVector(GetActorLocation().X, GetActorLocation().Y, 0.0);
		AttachedBall = GetWorld()->SpawnActor<ABreakoutBall>(Ball_BP, BallSpawn, GetActorRotation());

		ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
		if (GameState)
		{
			GameState->ModifyBallAmount(1);
		}
	}
}
void ABreakoutPlayerCharacter::ShootBall()
{
	float RandomHorizontal = FMath::RandRange(-100, 100);
	if (AttachedBall)
	{
		FVector BallVelocity = FVector(100.0, RandomHorizontal, 0.0);
		AttachedBall->Velocity = BallVelocity;
		AttachedBall = nullptr;
	}
}
void ABreakoutPlayerCharacter::OnOverlapBegin(AActor* Other)
{
	Super::OnOverlapBegin(Other);
	ABreakoutBall* Ball = Cast<ABreakoutBall>(Other);
	if (Ball)
	{
		if (PowerUpDuration > 0)
		{
			PowerUpDuration--;
		}
		if (PowerUpDuration == 0)
		{
			ResetPowerup();
		}
		if (FMath::Abs(Ball->Velocity.Y) <= 10)
		{
			Ball->Velocity.Y += Velocity.Y / 20;
		}
	}
}

void ABreakoutPlayerCharacter::ResetPowerup()
{
	FVector NewScale = FVector(1.0, 5.0, 1.0);
	PowerUpDuration = 0;
	SetActorScale3D(NewScale);
	SetBoundaries();
}