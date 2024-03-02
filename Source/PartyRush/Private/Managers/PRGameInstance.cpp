#include "PRGameInstance.h"



void UPRGameInstance::SetCurrentLevelName(FName LevelName)
{
	CurrLevelName = LevelName;
}

void UPRGameInstance::SetLevelCompleted(FName LevelName, bool bCompleted/* = true*/)
{
	if (bCompleted)
	{
		if (ArrayLevelsCompleted.Contains(LevelName)) return;
		ArrayLevelsCompleted.Add(LevelName);
	}
	else
	{
		if (!ArrayLevelsCompleted.Contains(LevelName)) return;
		ArrayLevelsCompleted.Remove(LevelName);
	}
}

bool UPRGameInstance::IsLevelCompleted(FName LevelName) const
{
	return ArrayLevelsCompleted.Contains(LevelName);
}

void UPRGameInstance::TriggerGameOver()
{
	OnLevelGameOver.Broadcast();
}

void UPRGameInstance::TriggerWin()
{
	SetLevelCompleted(InitRowName);
	OnLevelWin.Broadcast();
}

void UPRGameInstance::DEBUG_TriggerWin()
{
#if!(UE_BUILD_SHIPPING)
	TriggerWin();
#endif
}
