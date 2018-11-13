// Fill out your copyright notice in the Description page of Project Settings.

#include "View.h"


// Sets default values
AView::AView()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AView::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT("BeginPlay2233!!"));
	
	for (int32 i = 0; i < moverCount; ++i) {
		FTransform offset;
		int32 gridY = i % 10;
		int32 gridZ = FMath::FloorToInt(i / 10);
		float floorHeight = gridZ * cubeSize;
		FVector localPos = FVector(0, gridY * cubeSize, floorHeight + 100);
		offset.SetLocation(localPos);
		AMover* mover = CreateMover(offset);
		mover->acc.Z = -.1;
		mover->SetType(FMath::RandRange(0,5));
		//mover->gridY = gridY;
		//mover->gridZ = gridZ;

		localPos.Z -= 100;
		localPos = GetActorTransform().TransformPosition(localPos);
		mover->SetFloor(localPos.Z);
		mover->onDeadEvent.AddDynamic(this, &AView::doOnMoverDead);
		movers.Add(mover);
	}
}

void AView::doOnMoverDead(AMover* mover) {
	getCubeData();
}

AMover* AView::getMoverById(int32 pid) {
	FVector localPos = FVector(0, (pid % 10) * cubeSize, FMath::FloorToInt(pid / 10) * cubeSize);
	for (int32 i = movers.Num() - 1; i >= 0; --i) {
		AMover* mover = movers[i];
		FVector moverPos = mover->GetActorLocation();
		FVector localMoverPos = GetActorTransform().InverseTransformPosition(moverPos);
		if (localMoverPos == localPos) {
			return mover;
		}
	}
	return nullptr;
}

void AView::DoEatCube() {
	UE_LOG(LogTemp, Warning, TEXT("%s"), TEXT("DoEatCube2!!"));

	TArray<int32> eatCube;
	eatCube.Add(13);
	eatCube.Add(14);
	eatCube.Add(15);
	eatCube.Add(25);
	eatCube.Add(35);
	eatCube.Add(78);

	for (int32 i = 0; i < eatCube.Num(); ++i) {
		int32 pid = eatCube[i];
		AMover* mover = getMoverById(pid);
		if (mover != nullptr) {
			movers.Remove(mover);
			mover->Destroy();
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s"), "start to check!");

	TMap<int, float> tempData;
	for (int32 i = 0; i < moverCount; ++i) {
		AMover* mover = getMoverById(i);
		int32 gridY = i % 10;
		int32 gridZ = FMath::FloorToInt(i / 10);
		//UE_LOG(LogTemp, Warning, TEXT("check cube:%i, %i"), gridY, gridZ);
		if (mover == nullptr) {
			if (tempData.Contains(gridY)) {
				//UE_LOG(LogTemp, Warning, TEXT("has cube:%i"), gridY);
			}
			else {
				//UE_LOG(LogTemp, Warning, TEXT("no cube:%i, %i"), gridY, gridZ);
				tempData.Add(gridY, gridZ);
			}
		}
		else {
			if (tempData.Contains(gridY)) {
				//UE_LOG(LogTemp, Warning, TEXT("down cube:%f"), ((gridZ-1) * cubeSize) + GetActorLocation().Z);
				mover->SetFloor(((tempData[gridY]) * cubeSize) + GetActorLocation().Z);
				tempData[gridY] = tempData[gridY] + 1;
			}
			else {
				//tempData.Add(gridY, gridZ);
			}
		}
	}
	
	for (auto It = tempData.CreateConstIterator(); It; ++It) {
		int yId = It.Key();
		int zId = It.Value();
		while (zId < 10)
		{
			FTransform offset;
			FVector localPos = FVector(0, yId * cubeSize, 1000);
			offset.SetLocation(localPos);
			AMover* mover = CreateMover(offset);
			mover->acc.Z = -.1;
			mover->SetType(FMath::RandRange(0, 5));
			localPos.Z = zId * cubeSize;
			localPos = GetActorTransform().TransformPosition(localPos);
			mover->SetFloor(localPos.Z);
			movers.Add(mover);
			zId += 1;
		}
		UE_LOG(LogTemp, Warning, TEXT("yId:%i, zId:%i"), yId, zId);
	}
}

TArray<int> AView::getCubeData() {
	TArray<int> data;
	for (int32 i = 0; i < moverCount; ++i) {
		data.Add(0);
	}
	for (int32 i = 0; i < movers.Num(); ++i) {
		AMover* mover = movers[i];
		if (!mover->isActive) {
			FVector localPos = GetActorTransform().InverseTransformPosition(mover->GetActorLocation());
			int32 inArrayId = FMath::RoundToInt(localPos.Y / cubeSize) + (FMath::RoundToInt(localPos.Z / cubeSize)) * 10;
			data[inArrayId] = mover->GetType();
			//UE_LOG(LogTemp, Warning, TEXT("mover array id:%i"), inArrayId);
			//UE_LOG(LogTemp, Warning, TEXT("mover local pos:%s"), *localPos.ToString());
		}
		//UE_LOG(LogTemp, Warning, TEXT("mover local pos:%s"), *localPos.ToString());
	}
	return data;
}

// Called every frame
void AView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

