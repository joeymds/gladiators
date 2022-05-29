// Copyright @ 2022 Joey Matos Dos Santos

#include "PickableWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

APickableWeapon::APickableWeapon()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	MySphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	MySphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	MySkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Hammer"));
	MySkeletalMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	DamageBox->AttachToComponent(MySphere, FAttachmentTransformRules::KeepRelativeTransform);
}

void APickableWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

UBoxComponent* APickableWeapon::GetDamageBox() const
{
	return DamageBox;
}


