#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "PRInitInfo.h"
#include "PRGameInstance.generated.h"

class APRMenuManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelWin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelGameOver);

UCLASS()
class PARTYRUSH_API UPRGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetCurrentLevelName(FName LevelName);

	UFUNCTION(BlueprintCallable)
	void SetLevelCompleted(FName LevelName, bool bCompleted = true);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsLevelCompleted(FName LevelName) const;

	UFUNCTION(BlueprintCallable)
	void ResetAllLevelsCompletion() { ArrayLevelsCompleted.Empty(); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetInitRowName() const { return InitRowName; }

	UFUNCTION(BlueprintCallable)
	void SetInitRowName(FName NewRowName) { InitRowName = NewRowName; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDataTable* GetInitDT() const { return InitDT; }

	UFUNCTION(BlueprintCallable)
	void SetInitDT(UDataTable* NewDT) { InitDT = NewDT; }

	UFUNCTION()
	TSubclassOf<APRMenuManager> GetMenuManagerClass() { return MenuManagerClass; }

	UFUNCTION()
	void TriggerGameOver();

	UFUNCTION()
	void TriggerWin();

	FOnLevelGameOver OnLevelGameOver;
	FOnLevelWin OnLevelWin;

	/// PRDEBUG

	UFUNCTION(BlueprintCallable)
	void DEBUG_TriggerWin();

	///

protected:
	// Menu manager subclass
	UPROPERTY(EditAnywhere)
	TSubclassOf<APRMenuManager> MenuManagerClass;

private:
	UPROPERTY()
	FName CurrLevelName;

	UPROPERTY()
	TArray<FName> ArrayLevelsCompleted;

	// Name of the datatable's row where the init data is stored for current level
	UPROPERTY()
	FName InitRowName;

	// Datatable where the init data is stored
	UPROPERTY()
	UDataTable* InitDT;
};
