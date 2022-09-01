// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutPlayerController.h"
#include "Player/BreakoutPlayerCharacter.h"
#include "Player/BreakoutBall.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "BreakoutGameStateBase.h"
#include "../Shapes/LineShape.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void ABreakoutPlayerController::BeginPlay()
{
	CanSpawn = true;
	bHasGameEnded = false;

	Super::BeginPlay();
	SetUpPlayerController();

	if (WBallCounter_BP)
	{
		WBallCounter = CreateWidget<UUserWidget>(this, WBallCounter_BP);
		if (WBallCounter)
		{
			WBallCounter->AddToViewport();
			WBallCounter->SetVisibility(ESlateVisibility::Visible);
		}
	}

	if (WGameEnd_BP)
	{
		WGameEnd = CreateWidget<UUserWidget>(this, WGameEnd_BP);
		if (WGameEnd)
		{
			WGameEnd->AddToViewport();
			WGameEnd->SetVisibility(ESlateVisibility::Hidden);
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
	if (!bHasGameEnded)
	{
		TArray<AActor*> Balls;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakoutBall::StaticClass(), Balls);
		for (AActor* B : Balls)
		{
			ABreakoutBall* Ball = Cast<ABreakoutBall>(B);
			if(Ball)
			{
				FVector Location = Ball->GetActorLocation();
				if (Location.X > TopLimit)
					Ball->Kill();
				if (Location.Y > RightLimit + 200)
					Ball->Kill();
				if (Location.Y < LeftLimit - 200)
					Ball->Kill();
			}
		}
	}
	else
	{
		if (ResetLevelTimer > 0.0)
		{
			ResetLevelTimer -= Deltatime;
		}
		else
		{
			FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld(), false);
			UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()),true, "None");
		}
	}

}
void ABreakoutPlayerController::SetUpPlayerController()
{
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
	GameState->PlayerLives = 5;

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
		if (L->GetActorLocation().Y > TopLimit)
		{
			TopLimit = L->GetActorLocation().Y;
		}
	}
}

void ABreakoutPlayerController::Shoot()
{
	if (PlayerCharacter && !bHasGameEnded)
	{
		PlayerCharacter->ShootBall();
	}
}

void ABreakoutPlayerController::MoveRight(float Value)
{
	if (PlayerCharacter && !bHasGameEnded)
	{
		if (Value > 0.0)
		{
			if ((PlayerCharacter->GetActorLocation().Y + (PlayerCharacter->HorizontalSize* PlayerCharacter->GetActorScale().Y)) < RightLimit)
			{
				PlayerCharacter->MoveRight(Value);
				return;
			}
		}
		else if (Value < 0.0)
		{
			if ((PlayerCharacter->GetActorLocation().Y - (PlayerCharacter->HorizontalSize * PlayerCharacter->GetActorScale().Y)) > LeftLimit)
			{
				PlayerCharacter->MoveRight(Value);
				return;
			}
		}
		PlayerCharacter->MoveRight(0.0);
		
		
	}
}

void ABreakoutPlayerController::EndGame()
{
	bHasGameEnded = true;
	PlayerCharacter->Velocity = FVector(0.0f);
	WGameEnd->SetVisibility(ESlateVisibility::Visible);
	ResetLevelTimer = 3.0f;
}

void ABreakoutPlayerController::ActivateDebug()
{
	PhysicsEngine->ShouldDebug = true;
}

void ABreakoutPlayerController::DeactivateDebug()
{
	PhysicsEngine->ShouldDebug = false;
}
void ABreakoutPlayerController::RespawnBall()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->SpawnBall();
	}
	else
	{

		SetUpPlayerController();
		PlayerCharacter->SpawnCoolDown = 0.0f;
		PlayerCharacter->SpawnBall();
	}
}

