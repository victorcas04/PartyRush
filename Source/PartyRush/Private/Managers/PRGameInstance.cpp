#include "Managers/PRGameInstance.h"

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
