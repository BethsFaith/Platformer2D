// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPaperCharacter.h"

bool AEnemyPaperCharacter::IsAgressive()
{
	return bAggressive;
}

void AEnemyPaperCharacter::UpdateMovementAnimation()
{
	// если режим включен, смена анимации не произойдет
	if (!bAggressive) { 
		Super::UpdateMovementAnimation();
	}
}

void AEnemyPaperCharacter::Dead_Implementation()
{
	Super::Dead_Implementation();

	if (bAggressive) {
		TurnOffAggressiveMode();
	}
}

void AEnemyPaperCharacter::TurnOneAggressiveMode(ABasePaperCharacter* Target)
{
	if (Target == nullptr || bAggressive) { // если цель не указана или режим уже включен
 		return;
	}

	// включаем флаг
	bAggressive = true;

	// меняем анимацию
	PlayFlipbook(AgressiveMode, false);

	// умножаем скорость на модификатор
	auto MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed *= WalkingMultiplier;
}

void AEnemyPaperCharacter::TurnOffAggressiveMode()
{
	if (!bAggressive) { // если режим уже выключен
		return;
	}

	// возвращаем скорость
	auto MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed /= WalkingMultiplier;

	// выключаем флаг
	bAggressive = false;
}
