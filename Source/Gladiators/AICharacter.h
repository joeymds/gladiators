// Copyright @ 2022 Joey Matos Dos Santos

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "AICharacter.generated.h"


UCLASS()
class GLADIATORS_API AAICharacter : public AArenaCharacter
{
	GENERATED_BODY()

public:

	AAICharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APickableItemBase> Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APickableWeapon> Weapon;

	bool bCanDetectCollision;
	bool bDisableAttack;
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

public:

	void CreateAndAttachWeapons();

	UFUNCTION(BlueprintCallable)
	void TriggerAttack();

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepFrom, const FHitResult &SweepResult);
	
};
