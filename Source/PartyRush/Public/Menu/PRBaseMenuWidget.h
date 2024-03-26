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
	FName MenusRowName;

	UFUNCTION(BlueprintCallable)
	void CustomAddToViewport(int32 ZOrder = 0);

	UFUNCTION()
	void UnbindAllDelegates() { BP_UnbindAllDelegates(); }

protected:
	UPROPERTY(EditAnywhere)
	bool bIsPauseMenu{false};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	APRMenuManager* GetManager() { return WidgetManager; }

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<FName, TSubclassOf<UPRBaseMenuWidget>> GetMapSubmenusData() const { return MapSubmenusData; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TSubclassOf<UPRBaseMenuWidget> GetPopupWidget(FName PopupRowName, UDataTable* PopupDT = nullptr, FName MenusDataRowName = "Popups") const;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_UnbindAllDelegates();

private:
	UPROPERTY()
	TMap<FName, TSubclassOf<UPRBaseMenuWidget>> MapSubmenusData;

	UPROPERTY()
	APRMenuManager* WidgetManager;
};
