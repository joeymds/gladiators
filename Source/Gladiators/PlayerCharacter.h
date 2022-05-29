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

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Mouse_X(float Value);
	void Mouse_Y(float Value);
	
public:
	
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void TriggerAttack();
};
