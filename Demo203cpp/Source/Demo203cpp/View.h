// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mover.h"
#include "View.generated.h"

UCLASS()
class DEMO203CPP_API AView : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AView();

	UPROPERTY(EditAnywhere) TArray<AMover*> movers;
	UPROPERTY(EditAnywhere) int32 moverCount = 10;
	UPROPERTY(EditAnywhere) int32 cubeSize = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION() void doOnMoverDead(AMover* mover);
	UFUNCTION() AMover* getMoverById(int32 pid);
	TArray<int> getCubeData();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent) AMover* CreateMover(FTransform transform);
	UFUNCTION(BlueprintCallable) void DoEatCube();

};
