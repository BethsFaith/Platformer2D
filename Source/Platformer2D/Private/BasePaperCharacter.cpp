// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"

void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnimation(); // Анимация обновляется каждый тик
}

EMovementStatus ABasePaperCharacter::GetMovementStatus()
{
	auto velocity = GetVelocity();

	if (!velocity.IsZero()) {							  // активность?
		if (GetCharacterMovement()->IsMovingOnGround()) { // персонаж на земле?
			return EMovementStatus::VE_RUN;			      // бег
		}
		else if (GetVelocity().Z < 0)				      // падает?
			return EMovementStatus::VE_FALL;			  // в падении
		else
			return EMovementStatus::VE_JUMP;			  // в прыжке
	}
	else {
		return EMovementStatus::VE_IDLE;				  // в состоянии покоя
	}
}
