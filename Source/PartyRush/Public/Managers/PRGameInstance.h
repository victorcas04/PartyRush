#pragma once
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PRGameInstance.generated.h"

UCLASS()
class PARTYRUSH_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetLevelCompleted(FName LevelName, bool bCompleted = true);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsLevelCompleted(FName LevelName) const;

	UFUNCTION(BlueprintCallable)
	void ResetAllLevelsCompletion() { ArrayLevelsCompleted.Empty(); }

private:
	UPROPERTY()
	TArray<FName> ArrayLevelsCompleted;
};
