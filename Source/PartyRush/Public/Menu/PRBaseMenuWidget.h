#pragma once
#include "CoreMinimal.h"
#include "PRMenusInfo.h"
#include "Blueprint/UserWidget.h"
#include "PRBaseMenuWidget.generated.h"

class APRMenuManager;
UCLASS(BlueprintType)
class PARTYRUSH_API UPRBaseMenuWidget :  public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetManager(APRMenuManager* NewWidgetManager) { WidgetManager = NewWidgetManager; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsPauseMenu() const { return bIsPauseMenu; }
	
	// Datatable where the init data is stored
	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* MenusDT;

	// Name of the datatable's row where the menus data is stored for current submenu
	UPROPERTY(EditAnywhere, Category = "Data")
	FName DT_RowName;

	UFUNCTION(BlueprintCallable)
	void CustomAddToViewport(int32 ZOrder = 0);

protected:
	UPROPERTY(EditAnywhere)
	bool bIsPauseMenu{false};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	APRMenuManager* GetManager() { return WidgetManager; }

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<FName, TSubclassOf<UPRBaseMenuWidget>> GetMapSubmenusData() const { return MapSubmenusData; }

private:
	UPROPERTY()
	TMap<FName, TSubclassOf<UPRBaseMenuWidget>> MapSubmenusData;

	UPROPERTY()
	APRMenuManager* WidgetManager;
};
