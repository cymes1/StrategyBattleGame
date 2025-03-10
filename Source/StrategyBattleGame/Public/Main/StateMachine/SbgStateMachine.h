// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Main/StateMachine/SbgGameState.h"
#include "Utils/Global.h"
#include "Utils/SbgFolderInWorldOutliner.h"
#include "SbgStateMachine.generated.h"

UCLASS()
class STRATEGYBATTLEGAME_API ASbgStateMachine : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	USbgGameState* GameState;

public:
	ASbgStateMachine();

	template<class TState>
	void EnterState()
	{
		GameState = NewObject<TState>(this, TState::StaticClass(), typeid(TState).name());
		GameState->SetupAttachment(RootComponent);
	}
};