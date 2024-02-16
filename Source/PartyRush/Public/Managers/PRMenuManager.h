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

	// true if opened
	UFUNCTION()
	bool OpenPauseMenu();

	// false if closed
	UFUNCTION()
	bool ClosePauseMenu();

	UFUNCTION()
	void LevelWin();

	UFUNCTION()
	void LevelGameOver();

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
	bool bIsMenuOpen{false};

	UPROPERTY()
	bool bIsPauseMenu{false};
};
