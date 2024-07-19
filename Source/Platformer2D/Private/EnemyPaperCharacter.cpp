// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPaperCharacter.h"

bool AEnemyPaperCharacter::IsAgressive()
{
	return bAggressive;
}

void AEnemyPaperCharacter::UpdateMovementAnimation()
{
	// ���� ����� �������, ����� �������� �� ����������
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
	if (Target == nullptr || bAggressive) { // ���� ���� �� ������� ��� ����� ��� �������
 		return;
	}

	// �������� ����
	bAggressive = true;

	// ������ ��������
	PlayFlipbook(AgressiveMode, false);

	// �������� �������� �� �����������
	auto MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed *= WalkingMultiplier;
}

void AEnemyPaperCharacter::TurnOffAggressiveMode()
{
	if (!bAggressive) { // ���� ����� ��� ��������
		return;
	}

	// ���������� ��������
	auto MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed /= WalkingMultiplier;

	// ��������� ����
	bAggressive = false;
}
