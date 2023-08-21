#pragma once
#include "CoreMinimal.h"
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
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TSubclassOf<UPRBaseMenuWidget>> MapWidgetClasses;
	
	UPROPERTY(EditAnywhere)
	bool bIsPauseMenu{false};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	APRMenuManager* GetManager() { return WidgetManager; }

private:
	UPROPERTY()
	APRMenuManager* WidgetManager;
};
