// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicItem.generated.h"

UCLASS()
class BASICINVENTORY_API ABasicItem : public AActor
{
	GENERATED_BODY()
	
public:	

	ABasicItem();
	virtual void Tick(float DeltaTime) override;
	
	TWeakObjectPtr<AActor> GetOwner() const { return OwnerActor; }
	
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return ItemMesh; }
	FORCEINLINE FString GetItemName() const { return ItemName; }
	FORCEINLINE int32 GetQuantity() const { return Quantity; }
	FORCEINLINE void IncreaseQuantity() { ++Quantity; }
	FORCEINLINE void DecreaseQuantity() { --Quantity; }

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<AActor>	OwnerActor;

private:

	/** Skeletal Mesh for the item */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ItemMesh;

	/** Line trace collides with box to show HUD widgets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionSphere;

	/** Popup widget when looking at the item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* PickupWidget;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	int32 Quantity = 1;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Item Properties", meta = (AllowPrivateAccess = "true"))
	UTexture2D* ItemThumbnail;
	
};
