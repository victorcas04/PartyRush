#pragma once
#include "CoreMinimal.h"
#include "PRInitInfo.h"
#include "Engine/DataTable.h"
#include "PRInitManager.generated.h"

class APRMenuManager;
class APRGrid;
class APRCell;
class APRConga;
class APRCongaMember;
class UPRBaseMenuWidget;

UCLASS()
class PARTYRUSH_API APRInitManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	bool bIsInGameMap{true};

	// Menu manager subclass
	UPROPERTY(EditAnywhere)
	TSubclassOf<APRMenuManager> MenuManagerClass;
	
	// Menu widget to spawn
	UPROPERTY(EditAnywhere, Category="Menu", meta=(EditCondition="!bIsInGameMap"))
	TSubclassOf<UPRBaseMenuWidget> InitMenuClass;
	
	// Datatable where the init data is stored
	UPROPERTY(EditAnywhere, Category="InGame", meta=(EditCondition="bIsInGameMap"))
	UDataTable* InitDT;
	
	// Name of the datatable's row where the init data is stored for current level
	UPROPERTY(EditAnywhere, Category="InGame", meta=(EditCondition="bIsInGameMap"))
	FName DT_RowName;

	// Camera from the world to be used
	UPROPERTY(EditAnywhere, Category="InGame", meta=(EditCondition="bIsInGameMap"))
	ACameraActor* Camera;
	
	UFUNCTION(BlueprintCallable)
	void Init();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	FInitData InitData;
	
	UPROPERTY()
	APRGrid* Map;
	
	UPROPERTY()
	APRMenuManager* MenuManagerRef;

	UPROPERTY()
	bool bInitialized = false;
	
	UFUNCTION()
    bool InitMap();
   
    UFUNCTION()
    bool InitCongas();
   
    UFUNCTION()
    bool InitCamera() const;

	UFUNCTION()
	bool InitMapManager();
	
    UFUNCTION()
    bool InitInput();
};
