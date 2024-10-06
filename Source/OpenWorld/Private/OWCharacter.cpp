// AnnihilateSword


#include "OWCharacter.h"

#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Camera/CameraComponent.h>
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

AOWCharacter::AOWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = { false };
	bUseControllerRotationYaw = { false };
	bUseControllerRotationRoll = { false };

	// Character Movement Configuration
	GetCharacterMovement()->MaxWalkSpeed = { 600.0f };
	GetCharacterMovement()->bOrientRotationToMovement = { true };
	GetCharacterMovement()->RotationRate = { 0.0f, 520.0f, 0.0f };
	GetCharacterMovement()->AirControl = { 0.22f };
	GetCharacterMovement()->MaxAcceleration = { 1024.0f };
	GetCharacterMovement()->GroundFriction = { 1.0f };
	GetCharacterMovement()->BrakingDecelerationWalking = { 1024.0f };

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
	
	// Add Input Mapping Context.
	if (APlayerController* playerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(m_DefaultMappingContext, 0);
		}
	}
}

void AOWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &AOWCharacter::Move);
		enhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Triggered, this, &AOWCharacter::Look);

		enhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		enhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s', Failed to find an Enhanced input Component!!!"), *GetNameSafe(this));
	}
}

void AOWCharacter::Move(const FInputActionValue& value) noexcept
{
	if (Controller)
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator rotationYaw{ 0.0, rotation.Yaw, 0.0 };

		const FVector forwarDirection = FRotationMatrix(rotationYaw).GetUnitAxis(EAxis::X);
		const FVector rightDirection = FRotationMatrix(rotationYaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwarDirection, value.Get<FVector2D>().Y);
		AddMovementInput(rightDirection, value.Get<FVector2D>().X);
	}
}

void AOWCharacter::Look(const FInputActionValue& value) noexcept
{
	if (Controller)
	{
		AddControllerPitchInput(value.Get<FVector2D>().Y);
		AddControllerYawInput(value.Get<FVector2D>().X);
	}
}

void AOWCharacter::PlayFootstepAudio(bool bIsLeftFoot) noexcept
{
	UGameplayStatics::PlaySoundAtLocation(this, m_CueFootstep, GetActorLocation());
}

