// Copyright @ 2022 Joey Matos Dos Santos


#include "ArenaCharacter.h"
#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "Components/BoxComponent.h"

AArenaCharacter::AArenaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AArenaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArenaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AArenaCharacter::PickShield(APickableItemBase* PickedShield)
{
	if (!PickedShield)
		return false;

	if (!MyShield)
	{
		if (PickedShield->AttachItemTo(GetMesh(), TEXT("DualWeaponPoint")) == true)
		{
			MyShield = PickedShield;
			return true;
		}
	}
	return false;
}

bool AArenaCharacter::PickWeapon(APickableWeapon* PickedWeapon)
{
	if (!PickedWeapon)
		return false;

	if (!MyWeapon)
	{
		if (PickedWeapon->AttachItemTo(GetMesh(), TEXT("RightHandSocket")) == true)
		{
			MyWeapon = PickedWeapon;
			WeaponCollider = MyWeapon->GetDamageBox();
			WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Only want to collide on attack
			return true;
		}
	}
	return false;
}

void AArenaCharacter::Attack()
{
	bIsAttacking = true;
}

