#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "PRInitInfo.h"
#include "PRGameInstance.generated.h"

class APRMenuManager;

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

protected:
	// Menu manager subclass
	UPROPERTY(EditAnywhere)
	TSubclassOf<APRMenuManager> MenuManagerClass;

private:
	UPROPERTY()
	TArray<FName> ArrayLevelsCompleted;

	// Name of the datatable's row where the init data is stored for current level
	UPROPERTY()
	FName InitRowName;

	// Datatable where the init data is stored
	UPROPERTY()
	UDataTable* InitDT;
};
