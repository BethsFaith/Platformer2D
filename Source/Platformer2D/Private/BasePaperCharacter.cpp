// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePaperCharacter.h"

void ABasePaperCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAnimation(); // �������� ����������� ������ ���
}

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
