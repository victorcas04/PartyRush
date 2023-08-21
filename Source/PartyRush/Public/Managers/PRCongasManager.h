#pragma once
#include "CoreMinimal.h"
#include "PRCongaInfo.h"
#include "PRCongasManager.generated.h"

class APRGrid;
class APRCongaMember;

UCLASS()
class PARTYRUSH_API APRCongasManager : public AActor
{
	GENERATED_BODY()
	
public:
	static bool MergeCongas(APRGrid* GridRef, APRCongaMember* CurrentMember, APRCongaMember* OtherMember);
private:
	static EPRCongaMovementType GetMergeMovementType(EPRCongaMovementType NewCongaMovement, EPRCongaMovementType OldCongaMovement);
};
