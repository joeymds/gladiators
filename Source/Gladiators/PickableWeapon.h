// Copyright @ 2022 Joey Matos Dos Santos

#pragma once

#include "CoreMinimal.h"
#include "PickableItemBase.h"
#include "PickableWeapon.generated.h"

class UBoxComponent;
class USphereComponent;

UCLASS()
class GLADIATORS_API APickableWeapon : public APickableItemBase
{
	GENERATED_BODY()

public:

	APickableWeapon();

	virtual void BeginPlay() override;

	UBoxComponent* GetDamageBox() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* MySphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* MySkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DamageBox;
	
};
