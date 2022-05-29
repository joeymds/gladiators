// Copyright @ 2022 Joey Matos Dos Santos


#include "AICharacter.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "Components/BoxComponent.h"

AAICharacter::AAICharacter()
{
	
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateAndAttachWeapons();
	
}

void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsAttacking)
	{
		if (WeaponCollider != nullptr)
		{
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
	}
	else
	{
		if (WeaponCollider != nullptr)
		{
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			if (bCanDetectCollision)
				bCanDetectCollision = false;
		}
	}
	
}

void AAICharacter::CreateAndAttachWeapons()
{
	FVector Position = GetActorLocation();
	FRotator Rotation = GetActorRotation();

	if (Shield != nullptr)
	{
		APickableItemBase* NewShield = Cast<APickableItemBase>(GetWorld()->SpawnActor(Shield, &Position, &Rotation));
		NewShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint"));
	}

	if (Weapon != nullptr)
	{
		APickableWeapon* NewWeapon = Cast<APickableWeapon>(GetWorld()->SpawnActor(Weapon, &Position, &Rotation));
		NewWeapon->AttachItemTo(GetMesh(), TEXT("RightHandSocket"));

		WeaponCollider = NewWeapon->GetDamageBox();
		if (WeaponCollider != nullptr)
		{
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AAICharacter::OnWeaponBeginOverlap);
		}
	}

	
}

void AAICharacter::TriggerAttack()
{
	bCanDetectCollision = true;
	Attack();
}

void AAICharacter::OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bSweepFrom, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (bCanDetectCollision)
		{
			bCanDetectCollision = false;
			UE_LOG(LogTemp, Warning, TEXT("Collided with player"));
		}
	}
}
