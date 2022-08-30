// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutWorldLimit.h"
#include "Player/BreakoutBall.h"

void ABreakoutWorldLimit::OnOverlapBegin(AActor* Other)
{
	Super::OnOverlapBegin(Other);
	ABreakoutBall* Ball = Cast<ABreakoutBall>(Other);
	if (Ball)
	{
		Ball->Kill();
	}
}