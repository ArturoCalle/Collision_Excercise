// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/Player/BreakoutPlayerCharacter.h"
#include "../../Shapes/SquareShape.h"
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

	Paddle = GetWorld()->SpawnActor<ASquareShape>(SquareShapeBP,GetActorLocation(), GetActorRotation());
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::SnapToTarget, false);
	//Paddle->AttachToActor(this, AttachmentRules);
	Paddle->SetActorScale3D(FVector(1.0f, 5.0f, 1.0f));
	Paddle->SetBoundaries();
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
		FVector BallLocation = FVector(Paddle->GetActorLocation().X + Paddle->VerticalSize / 2 + AttachedBall->Radius, Paddle->GetActorLocation().Y , 0.0);
		AttachedBall->SetActorLocation(BallLocation);
	}

	

}

void ABreakoutPlayerCharacter::MoveRight(float Value)
{
	const FVector Direction = FVector::RightVector;
	Paddle->Velocity = Direction * (MovementSpeed * Value);
}
void ABreakoutPlayerCharacter::SpawnBall()
{
	if (SpawnCoolDown <= 0.0)
	{
		SpawnCoolDown = 0.5;
		FVector BallSpawn = FVector(Paddle->GetActorLocation().X, Paddle->GetActorLocation().Y, 0.0);
		AttachedBall = GetWorld()->SpawnActor<ABreakoutBall>(Ball_BP, BallSpawn, GetActorRotation());

		ABreakoutGameStateBase* GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());
		if (GameState)
		{
			GameState->ModifyBallAmount(1);
		}
	}
}
void  ABreakoutPlayerCharacter::ShootBall()
{
	if (AttachedBall)
	{
		FVector BallVelocity = FVector(150.0, Paddle->Velocity.Y, 0.0);
		AttachedBall->Velocity = BallVelocity;
		AttachedBall = nullptr;
	}
}