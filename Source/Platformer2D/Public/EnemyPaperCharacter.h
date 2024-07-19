// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePaperCharacter.h"
#include "EnemyPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API AEnemyPaperCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	bool IsAggressive();

protected:
	/* Переопределение */

	virtual void UpdateMovementAnimation() override;

	virtual void Dead_Implementation() override;

	// Функция вкл агрессивного режима
	UFUNCTION(BlueprintCallable)
	void TurnOneAggressiveMode(ABasePaperCharacter* Target);

	// Функция выкл агрессивного режима
	UFUNCTION(BlueprintCallable)
	void TurnOffAggressiveMode();

	/* Свойства */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations")
	UPaperFlipbook* AggressiveMode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AggressiveMode")
	int WalkingMultiplier;

private:
	bool bAggressive = false;
};
