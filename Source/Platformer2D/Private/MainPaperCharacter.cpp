// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPaperCharacter.h"

AMainPaperCharacter::AMainPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* создание компонентов (сразу отобразятся в редакторе bp-класса) */
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	auto Root = GetRootComponent(); 
	SpringArm->SetupAttachment(Root);  
	Camera->SetupAttachment(SpringArm);}

void AMainPaperCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	if (DefaultMappingContext != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AMainPaperCharacter::AddTreasure()
{
	++Treasures;
}
