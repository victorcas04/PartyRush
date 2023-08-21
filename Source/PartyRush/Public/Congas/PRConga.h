#pragma once
#include "CoreMinimal.h"
#include "PRGrid.h"
#include "Vector2DInt.h"
#include "PRConga.generated.h"

class APRCongaMember;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCongaMemberChangedLocation,
	APRCongaMember*, NewCongaMember, FVector2DInt, NewCoord, FVector2DInt, OldCoord, bool, bClearPreviousCellOnMove);

UCLASS(BlueprintType)
class PARTYRUSH_API APRConga : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	bool InitConga(TArray<FVector2DInt> NewCongaMembersPositions, TSubclassOf<APRCongaMember> NewCongaMemberSubclass, int32 NewCongaIdx, bool bPlayer = false);
	
	UFUNCTION()
	void AddNewMembers(TArray<APRCongaMember*> NewMembers, const APRCongaMember* CurrentMember, const APRCongaMember* OtherMember);
	
	UFUNCTION()
	TArray<APRCongaMember*> GetAllMembers() { return Members; }
	
	UFUNCTION()
	APRCongaMember* GetMemberFromPos(int32 Pos);

	UFUNCTION()
	bool IsCongaMemberHeadOrTail(const APRCongaMember* CongaMember) const;

	UFUNCTION()
	void SetSelected(const APRCongaMember* CellMember, bool bSelected);

	UFUNCTION()
	void SetMerged();
	
	UFUNCTION()
	void SetMovementTypeAllowed(EPRCongaMovementType NewMovementType);

	UFUNCTION()
	EPRCongaMovementType GetMovementTypeAllowed() const { return MovementTypeAllowed; }

	UFUNCTION()
	bool CheckCanMoveInDirection(EPRMovementType Direction) const;
	
	UFUNCTION()
	void MoveConga(EPRMovementType Direction, FVector2DInt NewPos);

	UFUNCTION()
	void UnbindMembers();
	
	FOnCongaMemberChangedLocation CongaMemberChangedLocation_Delegate;
	
private:
	UPROPERTY()
	TSubclassOf<class APRCongaMember> CongaMemberSubclass;
	
	UPROPERTY()
	TArray<APRCongaMember*> Members;

	UPROPERTY()
	int32 CongaIdx;
	
	UPROPERTY()
	EPRCongaMovementType MovementTypeAllowed;
	
	UFUNCTION()
	void SpawnCongaMember(FVector2DInt Coord, int32 NewCongaMemberIdx, bool bPlayer = false);

	UFUNCTION()
	void AddCongaMemberToConga(APRCongaMember* NewCongaMember);
	
	UFUNCTION()
	void FinishAddingMemberToConga(APRCongaMember* NewCongaMember);
	
	UFUNCTION()
	void CongaMemberChangedLocation(APRCongaMember* NewCongaMember, FVector2DInt NewCoord, FVector2DInt OldCoord, bool bClearPreviousCellOnMove);

	UFUNCTION()
	void MoveMembersOnConga(EPRMovementType Direction, FVector2DInt NewPos);
	
};
