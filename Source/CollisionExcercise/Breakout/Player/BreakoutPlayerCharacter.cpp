// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/Player/BreakoutPlayerCharacter.h"
#include "../../Shapes/SquareShape.h"
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
	
}

// Called every frame
void ABreakoutPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakoutPlayerCharacter::MoveRight(float Value)
{
	const FVector Direction = FVector::RightVector;
	Paddle->Velocity = Direction * (MovementSpeed * Value);
}
