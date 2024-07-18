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
		UpdateAnimation(); // �������� ����������� ������ ���
	}
}

//void ABasePaperCharacter::MoveForward(float Value)
//{
//	AddMovementInput({1.0, 0.0, 0.0 }, Value);					  // ������������ �� X � ��������� �� �������� Value (-1.0 ��� 1.0)
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

	if (!velocity.IsZero()) {							  // ����������?
		if (GetCharacterMovement()->IsMovingOnGround()) { // �������� �� �����?
			return EMovementStatus::VE_RUN;			      // ���
		}
		else if (GetVelocity().Z < 0)				      // ������?
			return EMovementStatus::VE_FALL;			  // � �������
		else
			return EMovementStatus::VE_JUMP;			  // � ������
	}
	else {
		return EMovementStatus::VE_IDLE;				  // � ��������� �����
	}
}

void ABasePaperCharacter::ChangeHP(float Points)
{
	HP += Points;

	if (Points > 0.0) {
		HP = (HP < MaxHP ? HP : MaxHP); // ���� �� ����� ������ ���������, �� ��������
	}
	else {
		HP = (HP >= 0.0 ? HP : 0.0);    // ���� �� ����� ������ ��������, �� ��������

		if (HP <= 0.0) {
			Dead();						// �������� ����� ������
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
