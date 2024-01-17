#pragma once
#include "CoreMinimal.h"
#include "PRCellInfo.h"
#include "PRCongaInfo.h"
#include "Vector2DInt.h"
#include "PRCongaMember.generated.h"

class APRConga;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCongaMemberUpdateLocation,
	APRCongaMember*, NewCongaMember, FVector2DInt, NewCoord, FVector2DInt, OldCoord, bool, bClearPreviousCellOnMove);

UCLASS(BlueprintType)
class PARTYRUSH_API APRCongaMember : public AActor
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static int32 CongaMember_GetSize() { return CONGAMEMBER_SIZE; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FLinearColor GetColor() { return GetColorByDirection(); }
	
	UFUNCTION()
	void SetIsPlayer(bool bNewIsPlayer);
	
	UFUNCTION()
	bool IsPlayer() const { return bIsPlayer; }

	UFUNCTION()
	bool IsLead() const { return bIsLead; }
	
	UFUNCTION()
	void SetLocationByCoord(FVector2DInt Coord);

	UFUNCTION()
	void SetCongaMemberColor() { BP_SetCongaMemberColor(GetColorByDirection()); }

	UFUNCTION()
	void SetCongaMemberSize() { BP_SetCongaMemberSize((float)CELL_SIZE); }

	UFUNCTION()
	void SetSelected(bool bSelected, bool bNewIsLead = false);

	// wrapper
	UFUNCTION()
	bool IsHeadOrTail() const;
	
	UFUNCTION()
	void SetCongaOwner(APRConga* Conga);

	UFUNCTION()
	APRConga* GetCongaOwner() { return CongaOwner; }

	UFUNCTION()
	void MoveLeader(FVector2DInt NewPos);

	UFUNCTION()
	void MoveNonLeader(const APRCongaMember* PreviousMember);

	UFUNCTION()
	void SetClearPreviousCellOnMove(bool bClear = false) { bClearPreviousCellOnMove = bClear; }
	
	UFUNCTION()
	void MoveFeedback(int32 MemberIdx) { BP_CongaMemberMoved(MemberIdx); }

	UFUNCTION()
	void MergeFeedback(int32 MemberIdx) { BP_CongaMemberMerged(MemberIdx); }
	
	FOnCongaMemberUpdateLocation CongaMemberUpdateLocation_Delegate;

	// this is for debug only, should never be used outside of that scope
	const FVector2DInt GetCurrentCoordDebug() { return CurrCoord; }
	
protected:
	UPROPERTY(EditAnywhere)
	float ZPos{50.0f};

	UPROPERTY(EditAnywhere)
	FLinearColor MainColor = FLinearColor::Blue;
	
	UPROPERTY(EditAnywhere)
	FLinearColor ColorHorizontal = FLinearColor::FromSRGBColor(FColor::Orange);

	UPROPERTY(EditAnywhere)
	FLinearColor ColorVertical = FLinearColor::FromSRGBColor(FColor::Green);

	UPROPERTY(EditAnywhere)
	FLinearColor ColorHorizontalAndVertical = FLinearColor::FromSRGBColor(FColor::Purple);

	UPROPERTY(EditAnywhere)
	FLinearColor ColorNone = FLinearColor::Gray;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor SelectedColor = FLinearColor::Yellow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor MergeColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeBeforeMoveFeedback{.1f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeBeforeMergeFeedback{.1f};
	
	UFUNCTION()
	FVector2DInt GetCurrentCoord() const { return CurrCoord; }
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_SetCongaMemberColor(FLinearColor NewColor);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_SetCongaMemberSize(float NewSize);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_SetCongaMemberSelected(bool bSelected, bool bLead = false);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_CongaMemberMoved(int32 MemberIdx);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_CongaMemberMerged(int32 MemberIdx);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_AdjustZPos();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetOriginalZPos() { return ZPos; }
	
private:
	UFUNCTION()
	FLinearColor GetColorByDirection();
	
	UPROPERTY()
	APRConga* CongaOwner;

	UPROPERTY()
	bool bIsPlayer{false};

	UPROPERTY()
	bool bIsLead{false};
	
	UPROPERTY()
	FVector2DInt CurrCoord;

	UPROPERTY()
	bool bClearPreviousCellOnMove{false};
	
	UFUNCTION()
	void AdjustZPos() { BP_AdjustZPos(); }
};
