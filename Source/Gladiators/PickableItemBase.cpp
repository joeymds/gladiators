// Copyright @ 2022 Joey Matos Dos Santos


#include "PickableItemBase.h"

#include "Engine/SkeletalMeshSocket.h"

// Sets default values
APickableItemBase::APickableItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickableItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickableItemBase::AttachItemTo(USkeletalMeshComponent* MeshRoot, FName Socket)
{
	if (IsUsed)
		return false;

	AttachToComponent(MeshRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);

	MeshRoot->GetSocketByName(Socket)->AttachActor(this, MeshRoot);
	SetActorRelativeLocation(FVector::ZeroVector);
	SetActorRelativeRotation(FRotator::ZeroRotator);
	IsUsed = true;
	return true;
}

