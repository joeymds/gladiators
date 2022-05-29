// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaCharacter.generated.h"

class APickableItemBase;
class APickableWeapon;
class UBoxComponent;

UCLASS()
class GLADIATORS_API AArenaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AArenaCharacter();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsAttacking = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsAlive = true;


protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:	

	bool PickShield(APickableItemBase* PickedShield);
	bool PickWeapon(APickableWeapon* PickedWeapon);

	APickableItemBase* MyShield;
	APickableWeapon* MyWeapon;

	UBoxComponent* WeaponCollider;

	void Attack();
};
