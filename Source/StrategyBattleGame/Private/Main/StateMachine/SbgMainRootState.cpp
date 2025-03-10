#include "Main/StateMachine/SbgMainRootState.h"

#include "Utils/Global.h"


USbgMainRootState::USbgMainRootState()
{}

void USbgMainRootState::EnterState()
{
	Super::EnterState();
	
	UE_LOG(LogSBG, Log, TEXT("ASbgMainRootState::EnterState"));
}

void USbgMainRootState::ExitState()
{
	Super::ExitState();
	
	UE_LOG(LogSBG, Log, TEXT("ASbgMainRootState::ExitState"));
}
