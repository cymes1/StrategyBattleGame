#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SbgGameState.generated.h"

UCLASS( ClassGroup=(SBG), meta=(BlueprintSpawnableComponent) )
class STRATEGYBATTLEGAME_API USbgGameState : public USceneComponent
{
	GENERATED_BODY()

public:
	USbgGameState();

	virtual void EnterState();
	virtual void TickState();
	virtual void ExitState();
};
