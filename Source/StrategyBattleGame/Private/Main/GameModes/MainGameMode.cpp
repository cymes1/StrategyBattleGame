#include "StrategyBattleGame/Public/Main/GameModes/MainGameMode.h"

#include "Main/StateMachine/SbgMainRootState.h"
#include "Main/StateMachine/SbgStateMachine.h"
#include "StrategyBattleGame/Public/Utils/Global.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogSBG, Log, TEXT("MainGameMode::BeginPlay"));
	CreateStateMachine();
}

void AMainGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyStateMachine();
	
	Super::EndPlay(EndPlayReason);
}

void AMainGameMode::CreateStateMachine()
{
	UE_LOG(LogSBG, Log, TEXT("MainGameMode::CreateStateMachine"));
	StateMachine = GetWorld()->SpawnActor<ASbgStateMachine>(ASbgStateMachine::StaticClass());
	
	#if WITH_EDITOR
	StateMachine->SetActorLabel(TEXT("MainStateMachine"));
	bool bResult;
	FString OutMessage;
	USbgFolderInWorldOutliner::MoveActorIntoFolder(StateMachine, OUTLINER_GAMEPLAY_STATE_MACHINE_DIR, bResult, OutMessage);
	if (!bResult)
		UE_LOG(LogSBG, Warning, TEXT("%s"), *OutMessage);
	#endif
	
	StateMachine->EnterState<USbgMainRootState>();
}

void AMainGameMode::DestroyStateMachine()
{
	StateMachine->Destroy();
	UE_LOG(LogSBG, Log, TEXT("MainGameMode::DestroyStateMachine"));
}
