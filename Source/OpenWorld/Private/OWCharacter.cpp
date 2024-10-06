// AnnihilateSword


#include "OWCharacter.h"

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>

AOWCharacter::AOWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = { false };
	bUseControllerRotationYaw = { false };
	bUseControllerRotationRoll = { false };

	// Character Movement Configuration


	// Spring Arm Component
	m_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	m_SpringArmComponent->SetupAttachment(RootComponent);
	m_SpringArmComponent->TargetArmLength = { 450.0f };
	m_SpringArmComponent->bUsePawnControlRotation = { true };

	// Camera Component
	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	m_CameraComponent->SetupAttachment(m_SpringArmComponent, USpringArmComponent::SocketName);
	m_CameraComponent->bUsePawnControlRotation = { false };
}

void AOWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOWCharacter::Move(const FInputActionValue& value) noexcept
{
}

void AOWCharacter::Look(const FInputActionValue& value) noexcept
{
}

