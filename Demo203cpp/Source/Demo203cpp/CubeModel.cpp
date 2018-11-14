// Fill out your copyright notice in the Description page of Project Settings.

#include "CubeModel.h"


// Sets default values
ACubeModel::ACubeModel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACubeModel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubeModel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<int32> ACubeModel::CalculateCubes(TArray<int32> cubes) {

	for (int32 i = 0; i < cubes.Num(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("%i"), cubes[i]);
	}

	TArray<int32> eatCube;
	eatCube.Add(13);
	eatCube.Add(14);
	eatCube.Add(15);
	eatCube.Add(25);
	eatCube.Add(35);
	eatCube.Add(78);
	return eatCube;
}

