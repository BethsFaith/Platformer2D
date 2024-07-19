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

	if (!bIsDead && bCanChangeAnimation) {
		UpdateMovementAnimation(); // �������� ����������� ������ ���
	}
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

void ABasePaperCharacter::UpdateMovementAnimation()
{
	auto status = GetMovementStatus();

	switch (status) {
	case(EMovementStatus::VE_IDLE): {
		PlayFlipbook(Idle, false);
		break;
	}
	case(EMovementStatus::VE_RUN): {
		PlayFlipbook(Run, false);
		break;
	}
	case(EMovementStatus::VE_JUMP): {
		PlayFlipbook(Up, false);
		break;
	}
	case(EMovementStatus::VE_FALL): {
		PlayFlipbook(Fall, false);
		break;
	}
	default:
		break;
	}
}

void ABasePaperCharacter::PlayFlipbook(UPaperFlipbook* Flipbook, bool PlayOneTime)
{
	auto sprite = GetSprite();
	
	if (Flipbook != nullptr) {
		sprite->SetFlipbook(Flipbook);

		if (PlayOneTime) {
			bCanChangeAnimation = false;

			GetWorld()->GetTimerManager().SetTimer(FlipbookPlayHandle, this, 
				&ABasePaperCharacter::PlayFlipbookFinished, Flipbook->GetTotalDuration(), false);
		}
	}
}

void ABasePaperCharacter::PlayFlipbookFinished()
{
	bCanChangeAnimation = true;
}

void ABasePaperCharacter::Damage(float Damage)
{
	if (Damage > 0.0) { 
		Damage *= -1;
	}

	changeHP(Damage);

	if (HP <= 0.0) {
		PlayFlipbook(DeadHit, true); // ����������� �������� ������������ �����
		
		Dead();						 // �������� ����� ������
	}
	else {
		PlayFlipbook(Hit, true);     // ����������� �������� �����
	}
}

void ABasePaperCharacter::Heal(float Heal_)
{
	if (Heal_ < 0.0) {
		Heal_ *= -1;
	}

	changeHP(Heal_);
}

void ABasePaperCharacter::Dead_Implementation()
{
	bIsDead = true;

	PlayFlipbook(Death, false);
}

bool ABasePaperCharacter::IsDead()
{
	return bIsDead;
}

void ABasePaperCharacter::changeHP(float Points)
{
	HP += Points;

	if (Points > 0.0) {
		HP = (HP < MaxHP ? HP : MaxHP); // ���� �� ����� ������ ���������, �� ��������
	}
	else {
		HP = (HP >= 0.0 ? HP : 0.0);    // ���� �� ����� ������ ��������, �� ��������
	}
}