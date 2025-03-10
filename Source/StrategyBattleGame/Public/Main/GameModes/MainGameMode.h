#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/ObjectPtr.h"
#include "MainGameMode.generated.h"

class ASbgStateMachine;

/**
 * 
 */
UCLASS()
class STRATEGYBATTLEGAME_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	TObjectPtr<ASbgStateMachine> StateMachine;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	void CreateStateMachine();
	void DestroyStateMachine();
};
