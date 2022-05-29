// Copyright @ 2022 Joey Matos Dos Santos

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItemBase.generated.h"

UCLASS()
class GLADIATORS_API APickableItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool AttachItemTo(USkeletalMeshComponent* MeshRoot, FName Socket);

	bool IsUsed;

};
