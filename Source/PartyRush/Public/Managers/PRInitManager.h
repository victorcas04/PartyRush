#pragma once
#include "CoreMinimal.h"
#include "PRInitInfo.h"
#include "PRInitManager.generated.h"

class APRMenuManager;
class APRGrid;
class APRCell;
class APRConga;
class APRCongaMember;
class UPRBaseMenuWidget;
class UPRGameInstance;

UCLASS()
class PARTYRUSH_API APRInitManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool bIsInGameMap{true};

	UFUNCTION(BlueprintCallable)
	void Init();

protected:
	virtual void BeginPlay() override;

	// Menu widget to spawn
	UPROPERTY(EditAnywhere, meta = (EditCondition = "!bIsInGameMap"))
	TSubclassOf<UPRBaseMenuWidget> InitMenuClass;

	// Datatable where the init data is stored
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsInGameMap", RowType = "FInitData"))
	UDataTable* OverridedInitDT;

	// Name of the datatable's row where the init data is stored for current level (this overrides whatever is saved in the GI)
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsInGameMap"))
	FName OverridedInitRowName;
	
private:
	UPROPERTY()
	UPRGameInstance* GI;

	UPROPERTY()
	FInitData InitData;
	
	UPROPERTY()
	APRGrid* Map;
	
	UPROPERTY()
	APRMenuManager* MenuManagerRef;

	UPROPERTY()
	bool bInitialized = false;

	UPROPERTY()
	FName InitRowName_Internal;

	UPROPERTY()
	UDataTable* InitDT_Internal;

	UFUNCTION()
    bool InitMap();
   
    UFUNCTION()
    bool InitCongas();
   
    UFUNCTION()
    bool InitCamera() const;

	UFUNCTION()
	bool InitMapManager();
	
    UFUNCTION()
    bool InitController();
};
