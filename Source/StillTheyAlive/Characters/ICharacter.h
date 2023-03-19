#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

class STILLTHEYALIVE_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void Hitted() = 0;
	virtual void Dead() = 0;
};
