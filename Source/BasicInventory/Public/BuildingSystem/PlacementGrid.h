// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacementGrid.generated.h"

UCLASS()
class BASICINVENTORY_API APlacementGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	APlacementGrid();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated, EditAnywhere, Category = "Placement Grid")
	float CellSize = 100.0f;

	UFUNCTION(BlueprintCallable, Category = "Placement Grid")
	FVector SnapToGrid(FVector WorldLocation);

	UFUNCTION(BlueprintCallable, Category = "Placement Grid")
	bool IsCellEmpty(FVector GridLocation);
	
	

protected:

	virtual void BeginPlay() override;

};
