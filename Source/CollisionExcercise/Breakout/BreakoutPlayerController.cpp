// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutPlayerController.h"
#include "Player/BreakoutPlayerCharacter.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "BreakoutGameStateBase.h"
#include "../Shapes/LineShape.h"
#include "Kismet/GameplayStatics.h"

void ABreakoutPlayerController::BeginPlay()
{
	CanSpawn = true;

	Super::BeginPlay();
	TArray<AActor*> PlayerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakoutPlayerCharacter::StaticClass(), PlayerArray);
	
	if (PlayerArray.Num() > 0)
	{
		PlayerCharacter = Cast<ABreakoutPlayerCharacter>(PlayerArray[0]);
		PlayerCharacter->PlayerController = this;
	}

	TArray<AActor*> Physics;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APhysicsEngine::StaticClass(), Physics);
	if (Physics.Num() > 0)
	{
		PhysicsEngine = Cast<APhysicsEngine>(Physics[0]);
	}

	GameState = Cast<ABreakoutGameStateBase>(GetWorld()->GetGameState());

	TArray<AActor*> Limits;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALineShape::StaticClass(), Limits);
	for (AActor* L : Limits)
	{
		if (L->GetActorLocation().Y < LeftLimit)
		{
			LeftLimit = L->GetActorLocation().Y;
		}
		if (L->GetActorLocation().Y > RightLimit)
		{
			RightLimit = L->GetActorLocation().Y;
		}
	}
}

void ABreakoutPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Debug", IE_Pressed, this, &ABreakoutPlayerController::ActivateDebug);
	InputComponent->BindAction("Debug", IE_Released, this, &ABreakoutPlayerController::DeactivateDebug);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ABreakoutPlayerController::Shoot);

	InputComponent->BindAxis("MoveRight", this, &ABreakoutPlayerController::MoveRight);
}

void ABreakoutPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}
void ABreakoutPlayerController::Shoot()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->ShootBall();
	}
}
void ABreakoutPlayerController::MoveRight(float Value)
{
	if (PlayerCharacter)
	{
		if (Value > 0.0)
		{
			if ((PlayerCharacter->GetActorLocation().Y + (PlayerCharacter->HorizontalSize*5)) < RightLimit)
			{
				PlayerCharacter->MoveRight(Value);
				return;
			}
		}
		else if (Value < 0.0)
		{
			if ((PlayerCharacter->GetActorLocation().Y - (PlayerCharacter->HorizontalSize*5)) > LeftLimit)
			{
				PlayerCharacter->MoveRight(Value);
				return;
			}
		}
		PlayerCharacter->MoveRight(0.0);
		
		
	}
}

void ABreakoutPlayerController::ActivateDebug()
{
	PhysicsEngine->ShouldDebug = true;
}
void ABreakoutPlayerController::DeactivateDebug()
{
	PhysicsEngine->ShouldDebug = false;
}
