// Copyright @ 2022 Joey Matos Dos Santos


#include "AICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "PlayerCharacter.h"
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
	if (bDisableAttack)
		return;
	
	bCanDetectCollision = true;
	Attack();
}

bool AAICharacter::ApplyDamage()
{
	Health -= 10.f;
	if (Health <= 0.f)
	{
		bIsAlive = false;
		AAIController* MyAIRef = Cast<AAIController>(GetController());
		// MyAIRef->BrainComponent->StopLogic(""); // another option
		MyAIRef->UnPossess();
		
		return true;
	}
	return false;
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
			APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
			bool bCanAttack = Player->ApplyDamage();

			bDisableAttack = bCanAttack;
		}
	}
}

