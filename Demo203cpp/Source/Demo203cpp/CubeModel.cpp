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
	// 盤面寬高
	const int W = 10;
	const int H = 10;
	
	// 有向圖資料
	bool linkLeft[W* H];
	bool linkUp[W* H];
	bool linkRight[W* H];
	bool linkDown[W* H];

	// 初使化有向圖資料
	for (int i = 0; i < W*H; ++i) {
		linkLeft[i] = false;
		linkUp[i] = false;
		linkRight[i] = false;
		linkDown[i] = false;
	}

	// 建立有向圖
	for (int i = 0; i < W*H; ++i) {
		int prevStyle = cubes[i];
		int row = i / W;
		// 連結上
		if (row > 0) {
			int up = i - W;
			int currStyle = cubes[up];
			if (prevStyle == currStyle) {
				linkUp[i] = true;
			}
		}
		// 連結下
		if (row < H - 1) {
			int down = i + W;
			int currStyle = cubes[down];
			if (prevStyle == currStyle) {
				linkDown[i] = true;
			}
		}
		
		int column = i % W;
		// 連結左
		if (column > 0) {
			int left = i - 1;
			int currStyle = cubes[left];
			if (prevStyle == currStyle) {
				linkLeft[i] = true;
			}
		}
		// 連結右
		if (column < W - 1) {
			int right = i + 1;
			int currStyle = cubes[right];
			if (prevStyle == currStyle) {
				linkRight[i] = true;
			}
		}
	}
	
	// 計算連結方塊
	TSet<int32> eatCube;
	TSet<int32> tmpCubes;

	for (int i = 0; i < W*H; ++i) {
		int startAt = i;
		// 重新計算
		tmpCubes.Reset();
		// 先加入原點
		tmpCubes.Add(startAt);

		// 先計算左右邊
		for (int currPos = startAt;;) {
			int column = currPos % W;
			if (column > 0) {
				bool hasLink = linkLeft[currPos];
				if (hasLink) {
					--currPos;
					tmpCubes.Add(currPos);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}

		for (int currPos = startAt;;) {
			int column = currPos % W;
			if (column < W - 1) {
				bool hasLink = linkRight[currPos];
				if (hasLink) {
					++currPos;
					tmpCubes.Add(currPos);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		
		// 如果連結數量大於3個, 就合併
		bool hasMoreThen3 = tmpCubes.Num() >= 3;
		if (hasMoreThen3) {
			// 合併
			eatCube = eatCube.Union(tmpCubes);
		}

		// 重新計算
		tmpCubes.Reset();
		// 先加入原點
		tmpCubes.Add(startAt);

		// 再計算上下
		for (int currPos = startAt;;) {
			int row = currPos / W;
			if (row > 0) {
				bool hasLink = linkUp[currPos];
				if (hasLink) {
					currPos -= W;
					tmpCubes.Add(currPos);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}

		for (int currPos = startAt;;) {
			int row = currPos / W;
			if (row < H - 1) {
				bool hasLink = linkDown[currPos];
				if (hasLink) {
					currPos += W;
					tmpCubes.Add(currPos);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}

		// 如果連結數量大於3個, 就合併
		hasMoreThen3 = tmpCubes.Num() >= 3;
		if (hasMoreThen3) {
			eatCube = eatCube.Union(tmpCubes);
		}
	}

	return eatCube.Array();
}

