// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"


// Sets default values
AMover::AMover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMover::BeginPlay()
{
	Super::BeginPlay();
}

void AMover::SetFloor(float floor) {
	this->floorHeight = floor;
	this->isActive = true;
}

void AMover::SetType(int type) {
	this->type = type;
	ChangeType(this->type);
}

int AMover::GetType() {
	return this->type;
}

// Called every frame
void AMover::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isActive) return;

	vel += acc;
	FVector pos = GetActorLocation();

	if (pos.Z < floorHeight) {
		pos.Z = floorHeight;
		vel.Z *= -.3;
	}

	SetActorLocation(pos + vel);

	if (spdHistory.Num() > 15) {
		spdHistory.RemoveAt(0);

		float spdaver = 0;
		for (int32 i = 0; i < spdHistory.Num(); ++i) {
			spdaver += spdHistory[i];
		}
		spdaver /= spdHistory.Num();

		if (spdaver < .3) {
			isActive = false;
			spdHistory.Empty();

			FVector pos = GetActorLocation();
			pos.X = FMath::RoundToInt(pos.X);
			pos.Y = FMath::RoundToInt(pos.Y);
			pos.Z = FMath::RoundToInt(pos.Z);
			SetActorLocation(pos);
			onDeadEvent.Broadcast(this);
		}
	}
	spdHistory.Add(vel.Size());

	
	
}

