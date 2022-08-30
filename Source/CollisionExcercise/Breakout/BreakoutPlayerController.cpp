// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutPlayerController.h"
#include "Player/BreakoutPlayerCharacter.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "Kismet/GameplayStatics.h"

void ABreakoutPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> PlayerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABreakoutPlayerCharacter::StaticClass(), PlayerArray);
	
	if (PlayerArray.Num() > 0)
	{
		PlayerCharacter = Cast<ABreakoutPlayerCharacter>(PlayerArray[0]);
	}

	TArray<AActor*> Physics;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APhysicsEngine::StaticClass(), Physics);
	if (Physics.Num() > 0)
	{
		PhysicsEngine = Cast<APhysicsEngine>(Physics[0]);
	}
}

void ABreakoutPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Debug", IE_Pressed, this, &ABreakoutPlayerController::ActivateDebug);
	InputComponent->BindAction("Debug", IE_Released, this, &ABreakoutPlayerController::DeactivateDebug);

	InputComponent->BindAxis("MoveRight", this, &ABreakoutPlayerController::MoveRight);
}

void ABreakoutPlayerController::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void ABreakoutPlayerController::MoveRight(float Value)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->MoveRight(Value);
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