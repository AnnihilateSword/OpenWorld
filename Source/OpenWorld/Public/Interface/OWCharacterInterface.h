// AnnihilateSword

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OWCharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UOWCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OPENWORLD_API IOWCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual void PlayFootstepAudio(bool bIsLeftFoot) noexcept = 0;
};