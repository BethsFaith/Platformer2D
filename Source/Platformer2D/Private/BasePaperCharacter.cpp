// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"

void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;
}

void ABasePaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsDead) {
		UpdateAnimation(); // Анимация обновляется каждый тик
	}
}

//void ABasePaperCharacter::MoveForward(float Value)
//{
//	AddMovementInput({1.0, 0.0, 0.0 }, Value);					  // Передвижение по X и умножение на значение Value (-1.0 или 1.0)
//
//	FRotator Rotator{ 0.0, 0.0, 0.0 };
//	if (Value < 0.0) {
//		Rotator = Rotator.Add(0.0, 0.0, 180.0);
//	}
//	
//	GetController()->SetControlRotation(Rotator); 
//}

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

void ABasePaperCharacter::ChangeHP(float Points)
{
	HP += Points;

	if (Points > 0.0) {
		HP = (HP < MaxHP ? HP : MaxHP); // если хп стало больше максимума, то заменяем
	}
	else {
		HP = (HP >= 0.0 ? HP : 0.0);    // если хп стало меньше минимума, то заменяем

		if (HP <= 0.0) {
			Dead();						// действия после смерти
		}
	}
}

void ABasePaperCharacter::Dead_Implementation()
{
	bIsDead = true;
}

bool ABasePaperCharacter::IsDead()
{
	return bIsDead;
}
