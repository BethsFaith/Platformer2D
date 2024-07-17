// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePaperCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "MainPaperCharacter.generated.h"

/**
 * 
 */

UCLASS()
class PLATFORMER2D_API AMainPaperCharacter : public ABasePaperCharacter
{
	GENERATED_BODY()
public:
	AMainPaperCharacter();

	// Начало игры
	virtual void BeginPlay() override;

	/* Свойства */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

protected:

private:
	APlayerController* PlayerController;
};
