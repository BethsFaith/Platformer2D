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

	if (!bIsDead && bCanChangeAnimation) { // если персонаж не мертв и можно менять анимацию
		UpdateMovementAnimation();		   // то анимация обновится в соответствии с движениями
	}
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

		if (PlayOneTime) {				   // если нужно проиграть один раз
			bCanChangeAnimation = false;   // запрещаем смену анимации 

			GetWorld()->GetTimerManager().SetTimer(FlipbookPlayHandle, this, 
				&ABasePaperCharacter::PlayFlipbookFinished, Flipbook->GetTotalDuration(), false); // ждем проигрывания анимации, после чего вызываем PlayFlipbookFinished()
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
		PlayFlipbook(DeadHit, true); // проигрываем анимацию смертельного удара
		
		Dead();						 // действия после смерти
	}
	else {
		PlayFlipbook(Hit, true);     // проигрываем анимацию удара
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

	if (bCanChangeAnimation) { // если можно сменить анимацию
		PlayDeathAnimation();  // меняем
	}
	else {
		GetWorld()->GetTimerManager().SetTimer(FlipbookPlayHandle, this,
			&ABasePaperCharacter::PlayDeathAnimation, DeadHit->GetTotalDuration(), false); // ждем проигрывания анимаций, чтобы включить death
	}
}

void ABasePaperCharacter::PlayDeathAnimation()
{
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
		HP = (HP < MaxHP ? HP : MaxHP); // если хп стало больше максимума, то заменяем
	}
	else {
		HP = (HP >= 0.0 ? HP : 0.0);    // если хп стало меньше минимума, то заменяем
	}
}