// AnnihilateSword

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/OWCharacterInterface.h"

#include "OWCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USoundCue;

struct FInputActionValue;

UCLASS()
class OPENWORLD_API AOWCharacter : public ACharacter, public IOWCharacterInterface
{
	GENERATED_BODY()

public:
	AOWCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/***********************/
	/** My Logic Functions */
	/***********************/
	void Move(const FInputActionValue& value) noexcept;
	void Look(const FInputActionValue& value) noexcept;

public:
	/*****************************/
	/** Interface Implementation */
	/*****************************/
	// Inherited via IOWCharacterInterface
	virtual void PlayFootstepAudio(bool bIsLeftFoot) noexcept override;

private:
	/***************/
	/** Properties */
	/***************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LayerTop|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> m_SpringArmComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LayerTop|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> m_CameraComponent{};

	// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LayerTop|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> m_DefaultMappingContext{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LayerTop|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> m_MoveAction{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LayerTop|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> m_LookAction{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LayerTop|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> m_JumpAction{};

	// Audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LayerTop|Audio", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundCue> m_CueFootstep{};
};
