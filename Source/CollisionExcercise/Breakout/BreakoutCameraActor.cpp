// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakout/BreakoutCameraActor.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABreakoutCameraActor::ABreakoutCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("StaticCamera"));
	SetRootComponent(Camera);
}

// Called when the game starts or when spawned
void ABreakoutCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABreakoutCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

