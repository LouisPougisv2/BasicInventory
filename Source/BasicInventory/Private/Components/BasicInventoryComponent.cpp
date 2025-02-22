// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BasicInventoryComponent.h"

#include "Actors/BasicItem.h"
#include "Blueprint/UserWidget.h"

UBasicInventoryComponent::UBasicInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBasicInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBasicInventoryComponent::AddItem(ABasicItem* ItemToAdd)
{
	//Since ItemToAdd is to be destroyed from the world (next Blueprint Node), we create a copy of it, that'll be added to the inventory 
	FObjectDuplicationParameters Parameters = FObjectDuplicationParameters(ItemToAdd,GetTransientPackage());
	ABasicItem* NewItem = Cast<ABasicItem>(StaticDuplicateObjectEx(Parameters));
	if(!NewItem) return;
	//{
	//	Items.Add(NewItem);
	//}
	//else
	//{
	//	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, *FString::Printf(TEXT("ItemToAdd in AddItem NOT VALID")));
	//}
	//if(!ItemToAdd) return;
	//
	////if(!Items.Contains(ItemToAdd))
	////{
	////	Items.Add(ItemToAdd);
	////}
	////else
	////{
	////	for(int i = 0; i < Items.Num(); ++i)
	////	{
	////		//If we already have the item in the inventory, increase stack
	////		if(Items[i].Get()->GetItemName() == ItemToAdd->GetItemName())
	////		{
	////			Items[i].Get()->IncreaseQuantity();
	////			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Green, *FString::Printf(TEXT("Item count -> %d"), Items[i].Get()->GetQuantity()));
	////		}
	////	}
	////}
	if(Items.IsEmpty())
	{
		Items.Add(NewItem);
		return;
	}
	for(int i = 0; i < Items.Num(); ++i)
	{
		//If we already have the item in the inventory, increase stack
		if(Items[i] && Items[i]->GetItemName() == NewItem->GetItemName())
		{
			Items[i]->IncreaseQuantity();
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Green, *FString::Printf(TEXT("Item count -> %d"), Items[i]->GetQuantity()));
			return;
		}
	}
	//Item not in inventory yet
	Items.Add(NewItem);
	
}

void UBasicInventoryComponent::DropItem(int32 IndexItemInInventory)
{
	if(!Items.IsEmpty() && Items[IndexItemInInventory])
	{
		//We get the item before removing it from the inventory, so we can spawn it after removal
		ABasicItem* ItemToDrop = Items[IndexItemInInventory];
		if(ItemToDrop->GetQuantity() > 1)
		{
			Items[IndexItemInInventory]->DecreaseQuantity();
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Green, *FString::Printf(TEXT("Item count -> %d"), Items[IndexItemInInventory]->GetQuantity()));
		}
		else
		{
			Items.RemoveAt(IndexItemInInventory);
		}

		//Spawning item in the world
		FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(-100.0f, 0.0f, 150.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		FTransform ItemSpawnTransform;
		ItemSpawnTransform.SetLocation(SpawnLocation);
		ItemSpawnTransform.SetRotation(SpawnRotation.Quaternion());
		
		ABasicItem* DroppedItem = GetWorld()->SpawnActorDeferred<ABasicItem>(ItemToDrop->GetClass(), ItemSpawnTransform, ItemToDrop->GetOwner().Get(), Cast<APawn>(ItemToDrop->GetOwner().Get()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if(DroppedItem)
		{
			DroppedItem->GetMesh()->SetSimulatePhysics(true);
			DroppedItem->SetActorEnableCollision(true);
			DroppedItem->GetMesh()->SetUseCCD(true);
			DroppedItem->GetMesh()->AddImpulse(GetOwner()->GetActorForwardVector()  * 300.0f);
			DroppedItem->FinishSpawning(ItemSpawnTransform);
			GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, *FString::Printf(TEXT("Item Dropped")));
		}
		
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, *FString::Printf(TEXT("Item removed Actor")));
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, *FString::Printf(TEXT("Inventory size : %d"), Items.Num()));
	}
}

//Array<FString> UBasicInventoryComponent::GetItemList() const
//
//	TArray<FString> ItemNames;
//	for (const TObjectPtr<ABasicItem>& Item : Items)
//	{
//		if (Item)
//		{
//			ItemNames.Add(Item->GetItemName());
//		}
//	}
//	return ItemNames;
//

//TArray<ABasicItem*> UBasicInventoryComponent::GetItems() const
//{
//	TArray<ABasicItem*> Results;
//	
//	for (const TObjectPtr<ABasicItem>& Item : Items)
//	{
//		if (Item)
//		{
//			Results.Add(Item.Get());
//		}
//	}
//	return Results;
//}
