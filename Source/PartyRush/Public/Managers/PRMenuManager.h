#pragma once
#include "CoreMinimal.h"
#include "PRMenuManager.generated.h"

class UPRBaseMenuWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelStatusChanged);

UCLASS(BlueprintType)
class PARTYRUSH_API APRMenuManager : public AActor
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Init(TSubclassOf<UPRBaseMenuWidget> InitMenuClass);
	
	UFUNCTION(BlueprintCallable)
	void SetIsMenuOpen(bool bNewIsMenuOpen, bool bIsNewPauseMenu = false);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsMenuOpen() { return bIsMenuOpen; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsPauseMenu() { return bIsPauseMenu; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsPopup() { return PopupRef != nullptr; }

	// true if opened
	UFUNCTION()
	bool OpenPauseMenu();

	// true if closed
	UFUNCTION()
	bool ClosePauseMenu();

	// true if opened
	UFUNCTION(BlueprintCallable)
	bool OpenPopup(UPRBaseMenuWidget* NewPopupRef);

	// true if closed
	UFUNCTION(BlueprintCallable)
	bool ClosePopup();

	UFUNCTION()
	void LevelWin();

	UFUNCTION()
	void LevelGameOver();

	UFUNCTION()
	void LevelCommon(UPRBaseMenuWidget* Screen);

	FOnLevelStatusChanged OnLevelStatusChanged;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPRBaseMenuWidget> PauseMenuClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPRBaseMenuWidget> WinScreenClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPRBaseMenuWidget> GameOverScreenClass;
	
private:
	UPROPERTY()
	UPRBaseMenuWidget* PauseMenuRef;
	
	UPROPERTY()
	UPRBaseMenuWidget* PopupRef;

	UPROPERTY()
	bool bIsMenuOpen{false};

	UPROPERTY()
	bool bIsPauseMenu{false};
};
