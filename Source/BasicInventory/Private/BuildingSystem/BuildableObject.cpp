// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/BuildableObject.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ABuildableObject::ABuildableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	SetReplicates(true);
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BuildableObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuidableObjectMesh"));
	BuildableObjectMesh->SetupAttachment(RootComponent);

}

void ABuildableObject::ServerPlaceObject_Implementation(const FVector& Location, const FRotator& Rotation)
{
	ClientPlaceObject(Location, Rotation);
}

bool ABuildableObject::ServerPlaceObject_Validate(const FVector& Location, const FRotator& Rotation)
{
	//Add Player's Inventory check in this function
	//return IsPlacementValid(Location, Rotation);
	if(IsPlacementValid(Location, Rotation))
	{
		return true;
	}
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Emerald, TEXT("ServerPlaceObject_Validate, Desired object Placement Invalid"));
	}
	return false;
}

void ABuildableObject::ClientPlaceObject_Implementation(const FVector& Location, const FRotator& Rotation)
{
	SetActorLocationAndRotation(Location, Rotation);
}

bool ABuildableObject::IsPlacementValid(const FVector& Location, const FRotator& Rotation)
{
	FCollisionQueryParams CollisionQueryParams;
	FHitResult HitResult;
	return !GetWorld()->LineTraceSingleByChannel(HitResult, Location, Location + FVector(0, 0, -100), ECollisionChannel::ECC_WorldStatic, CollisionQueryParams);
}

void ABuildableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildableObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

