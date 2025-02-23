// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasicItem.h"
#include "BasicInventory/BasicInventoryCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ABasicItem::ABasicItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetSimulatePhysics(true);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->SetSphereRadius(160.0f);
	
	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickUpWidget"));
	PickupWidget->SetupAttachment(GetRootComponent());
	PickupWidget->SetVisibility(false);
}

void ABasicItem::Destroyed()
{
	if(PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), GetActorRotation());
	}

	if(PickupParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, PickupParticles, GetActorLocation(), GetActorRotation());
	}
	Super::Destroyed();
}

// Called when the game starts or when spawned
void ABasicItem::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABasicItem::ABasicItem::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &ABasicItem::ABasicItem::OnOverlapEnd);

	PickupWidget->SetVisibility(false);

}

void ABasicItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(PickupWidget))
	{
		PickupWidget->SetVisibility(true);
	}

	ABasicInventoryCharacter* OverlappingPlayer = Cast<ABasicInventoryCharacter>(OtherActor);
	if(IsValid(OverlappingPlayer))
	{
		OverlappingPlayer->SetOverlappingActor(this);
	}
}

void ABasicItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(IsValid(PickupWidget))
	{
		PickupWidget->SetVisibility(false);
		
	}

	ABasicInventoryCharacter* OverlappingPlayer = Cast<ABasicInventoryCharacter>(OtherActor);
	if(IsValid(OverlappingPlayer))
	{
		OverlappingPlayer->SetOverlappingActor(nullptr);
	}
}

void ABasicItem::PlayDropEffects()
{
	if(DropSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DropSound, GetActorLocation(), GetActorRotation());
	}
	
	if(DropParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DropParticles, GetActorLocation(), GetActorRotation());
	}
}

// Called every frame
void ABasicItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

