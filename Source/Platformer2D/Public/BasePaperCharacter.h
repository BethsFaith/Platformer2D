// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

#include "BasePaperCharacter.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMovementStatus : uint8 {
	VE_IDLE UMETA(DisplayName = "Idle"),
	VE_RUN UMETA(DisplayName = "Run"),
	VE_JUMP  UMETA(DisplayName = "Jump"),
	VE_FALL  UMETA(DisplayName = "Fall"),
};

UCLASS()
class PLATFORMER2D_API ABasePaperCharacter : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	// Начало игры
	virtual void BeginPlay() override;

	// Вызывается каждый фрейм
	virtual void Tick(float DeltaTime) override;

	// Функция для определения текущего движения 
	UFUNCTION(BlueprintCallable)
	EMovementStatus GetMovementStatus();

	// Лечение
	UFUNCTION(BlueprintCallable)
	void Heal(float Heal_);

	// Ивент вызываемый при смерти
	UFUNCTION(BlueprintNativeEvent)
	void Dead();
	virtual void Dead_Implementation();

	UFUNCTION(BlueprintCallable)
	bool IsDead();

protected:
	// Функция для смены анимации
	UFUNCTION(BlueprintCallable)
	void UpdateMovementAnimation();

	FTimerHandle FlipbookPlayHandle;

	// Функция для смены анимации
	UFUNCTION(BlueprintCallable)
	void PlayFlipbook(UPaperFlipbook* Flipbook, bool PlayOneTime);

	UFUNCTION()
	void PlayFlipbookFinished();

	// Получение урона
	UFUNCTION(BlueprintCallable)
	void Damage(float Damage_);

	/* Свойства */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float DamageStrength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Idle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Run;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Up;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Fall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Hit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* DeadHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* Death;

private:
	// Функция для изменения хп
	void changeHP(float Points);

	bool bIsDead = false;
	bool bCanChangeAnimation = true;
};
