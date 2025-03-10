#pragma once

#include "CoreMinimal.h"
#include "Main/StateMachine/SbgGameState.h"
#include "SbgMainRootState.generated.h"

UCLASS()
class STRATEGYBATTLEGAME_API USbgMainRootState : public USbgGameState
{
	GENERATED_BODY()

public:
	USbgMainRootState();

	virtual void EnterState() override;
	virtual void ExitState() override;
};
