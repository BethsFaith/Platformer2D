// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"

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
	// ������ ����
	virtual void BeginPlay() override;

	// ���������� ������ �����
	virtual void Tick(float DeltaTime) override;

	// ������� ��� ����������� �������� �������� 
	UFUNCTION(BlueprintCallable)
	EMovementStatus GetMovementStatus();

	//// ����� ���������� ��� ��������� �����
	//UFUNCTION(BlueprintImplementableEvent)
	//void WasDamaged();

	// ����� ���������� ��� ������
	UFUNCTION(BlueprintNativeEvent)
	void Dead();
	virtual void Dead_Implementation();

	UFUNCTION(BlueprintCallable)
	bool IsDead();

protected:
	// ������� ��� ����� �������� (����������� � ��)
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAnimation();

	//// ������� ��� �������� 
	//UFUNCTION(BlueprintCallable)
	//void MoveForward(float Value);

	// ������� ��� ��������� ��
	UFUNCTION(BlueprintCallable)
	void ChangeHP(float Points);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage;

private:
	bool bIsDead = false;
};
