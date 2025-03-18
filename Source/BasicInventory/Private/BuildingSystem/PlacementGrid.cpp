// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/PlacementGrid.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

APlacementGrid::APlacementGrid()
{
	PrimaryActorTick.bCanEverTick = false;

}

void APlacementGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlacementGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlacementGrid::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlacementGrid, CellSize);
}

FVector APlacementGrid::SnapToGrid(FVector WorldLocation)
{
	return FVector(
		FMath::RoundToInt(WorldLocation.X / CellSize) * CellSize,
		FMath::RoundToInt(WorldLocation.Y / CellSize) * CellSize,
		FMath::RoundToInt(WorldLocation.Z / CellSize) * CellSize
		);
}

bool APlacementGrid::IsCellEmpty(FVector GridLocation)
{
	TArray<AActor*> OverlappingActors;
	TArray<AActor*> ActorsToIgnore;
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(CellSize * 0.5f));
	
	bool bTestOverlap = UKismetSystemLibrary::BoxOverlapActors(
		this,
		GridLocation,
		Shape.GetExtent(),
		TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic)},
		AActor::StaticClass(),
		ActorsToIgnore,
		OverlappingActors);

	if (bTestOverlap)
	{
		for (AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp, Log, TEXT("Overlapped Actor: %s"), *Actor->GetName());
		}
	}
	return OverlappingActors.Num() == 0;
}

