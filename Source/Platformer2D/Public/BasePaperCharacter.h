// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	// Функция для определения текущего движения (вызывается в бп)
	UFUNCTION(BlueprintCallable)
	EMovementStatus GetMovementStatus();
};
