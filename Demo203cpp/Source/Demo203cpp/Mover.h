// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mover.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDead, AMover*, mover);

UCLASS()
class DEMO203CPP_API AMover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMover();

	UPROPERTY(EditAnywhere) FVector acc;
	UPROPERTY(EditAnywhere) FVector vel;
	UPROPERTY(EditAnywhere) TArray<float> spdHistory;
	bool isActive = true;
	int32 gridY;
	int32 gridZ;

	FOnDead onDeadEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int type = 0;
	float floorHeight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent) void ChangeType(int type);
	UFUNCTION() void SetFloor(float floor);
	UFUNCTION() void SetType(int type);
	UFUNCTION() int GetType();

};
