// Copyright @ 2022 Joey Matos Dos Santos

#pragma once

#include "CoreMinimal.h"
#include "ArenaCharacter.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class GLADIATORS_API APlayerCharacter : public AArenaCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	float Health = 100.f;

	bool bAddedOverlapToWeapon;
	bool bCanDetectCollision;

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Mouse_X(float Value);
	void Mouse_Y(float Value);
	
public:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweepFrom, const FHitResult &SweepResult);

	void TriggerAttack();

	bool ApplyDamage();
	void RestartGame();
	
};
