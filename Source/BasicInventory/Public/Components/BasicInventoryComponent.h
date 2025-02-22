// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASICINVENTORY_API UBasicInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UBasicInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(class ABasicItem* ItemToAdd);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(int32 IndexItemInInventory);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<ABasicItem*> GetItems() { return Items; }

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Inventory")
	class UUserWidget* InventoryWidget;
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<ABasicItem*> Items;

		
};
