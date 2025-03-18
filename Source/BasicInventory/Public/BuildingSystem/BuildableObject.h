// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildableObject.generated.h"

UCLASS()
class ABuildableObject : public AActor
{
	GENERATED_BODY()
	
public:	

	ABuildableObject();

	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	UStaticMeshComponent* BuildableObjectMesh;

	UPROPERTY(EditDefaultsOnly,	BlueprintReadOnly, Category = "Building")
	FVector Size;

	UPROPERTY(EditDefaultsOnly,	BlueprintReadOnly, Category = "Building")
	int32 Cost;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPlaceObject(const FVector& Location, const FRotator& Rotation);

	UFUNCTION(Client, Reliable)
	void ClientPlaceObject(const FVector& Location, const FRotator& Rotation);

	UFUNCTION()
	bool IsPlacementValid(const FVector& Location, const FRotator& Rotation);
protected:

	virtual void BeginPlay() override;

};
