// Copyright @ 2022 Joey Matos Dos Santos

#include "PlayerCharacter.h"

#include "PickableItemBase.h"
#include "PickableWeapon.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Mouse_X", this, &APlayerCharacter::Mouse_X);
	PlayerInputComponent->BindAxis("Mouse_Y", this, &APlayerCharacter::Mouse_Y);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::TriggerAttack);
	
}

void APlayerCharacter::MoveForward(float Value)
{
	if (!bIsAlive)
		return;
	
	if (!bIsAttacking)
	{
		FRotator CameraRotation = GetControlRotation();
		CameraRotation.Pitch = 0.0f;
		const FVector MoveDirection = CameraRotation.Vector();

		GetCharacterMovement()->AddInputVector(MoveDirection * Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (!bIsAlive)
		return;
	
	if (!bIsAttacking)
	{
		FRotator CameraRotation = GetControlRotation();
		CameraRotation.Pitch = 0.0f;
		const FVector MoveDirection = CameraRotation.RotateVector(FVector::RightVector);

		GetCharacterMovement()->AddInputVector(MoveDirection * Value);
	}
}

void APlayerCharacter::Mouse_X(float Value)
{
	const float Input = Value * 100.f * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Input);
}

void APlayerCharacter::Mouse_Y(float Value)
{
	const float Input = Value * 100.f * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(Input);
}

void APlayerCharacter::TriggerAttack()
{
	if (MyWeapon)
	{
		Attack();	
	}
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Shield"))
	{
		APickableItemBase* PickedShield = Cast<APickableItemBase>(OtherActor);
		PickShield(PickedShield);
	}

	if (OtherActor->ActorHasTag("Hammer"))
	{
		APickableWeapon* PickedWeapon = Cast<APickableWeapon>(OtherActor);
		PickWeapon(PickedWeapon);
	}
}