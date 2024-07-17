// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"

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

	// Функция для смены анимации (реализуется в бп)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAnimation();

	// Ивент вызываемый при получение урона
	UFUNCTION(BlueprintImplementableEvent)
	void WasDamaged();

	// Функция для определения текущего движения 
	UFUNCTION(BlueprintCallable)
	EMovementStatus GetMovementStatus();

	// Функция для изменения хп
	UFUNCTION(BlueprintCallable)
	void ChangeHP(float Points);

	// Ивент вызываемый при смерти
	UFUNCTION(BlueprintNativeEvent)
	void Dead();
	virtual void Dead_Implementation();

	UFUNCTION(BlueprintCallable)
	bool IsDead();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage;

private:
	bool bIsDead = false;
};
