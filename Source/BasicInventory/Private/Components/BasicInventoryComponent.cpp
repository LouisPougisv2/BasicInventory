// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BasicInventoryComponent.h"
#include "Actors/BasicItem.h"

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

	//Store the Owner of the item (aka the player) for future use when adding impulse in DropItem()]
	NewItem->SetOwnerActor(GetOwner());
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
		}
		else
		{
			Items.RemoveAt(IndexItemInInventory);
		}

		//Spawning item in the world
		FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(150.0f, 0.0f, 150.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		FTransform ItemSpawnTransform;
		ItemSpawnTransform.SetLocation(SpawnLocation);
		ItemSpawnTransform.SetRotation(SpawnRotation.Quaternion());

		AActor* ItemOwner = ItemToDrop->GetOwner().Get();
		ABasicItem* DroppedItem = GetWorld()->SpawnActorDeferred<ABasicItem>(ItemToDrop->GetClass(), ItemSpawnTransform, ItemOwner, Cast<APawn>(ItemOwner), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		if(DroppedItem)
		{
			DroppedItem->GetMesh()->SetSimulatePhysics(true);
			DroppedItem->SetActorEnableCollision(true);
			DroppedItem->GetMesh()->SetUseCCD(true);
			DroppedItem->FinishSpawning(ItemSpawnTransform);
			if(IsValid(DroppedItem->GetMesh()) && IsValid(DroppedItem->GetOwner().Get()))
			{
				DroppedItem->GetMesh()->AddImpulse(DroppedItem->GetOwner().Get()->GetActorForwardVector() * FVector(50000.0f, 0.0f, 50000.0f));
			}
		}
	}
}
