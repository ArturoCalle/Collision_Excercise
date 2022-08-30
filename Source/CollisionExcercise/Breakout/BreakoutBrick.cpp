// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutBrick.h"

void ABreakoutBrick::OnOverlapBegin(AActor* Other)
{
	Super::OnOverlapBegin(Other);
	UE_LOG(LogTemp, Warning, TEXT("I'm a brick"));
}