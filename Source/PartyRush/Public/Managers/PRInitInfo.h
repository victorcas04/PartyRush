#pragma once
#include "CoreMinimal.h"
#include "Vector2DInt.h"
#include "PRCongaInfo.h"
#include "Engine/DataTable.h"
#include "PRInitInfo.generated.h"

class APRConga;
class APRCongaMember;
class APRGrid;
class APRCell;

USTRUCT(BlueprintType)
struct PARTYRUSH_API FInitData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APRGrid> GridSubclass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APRCell> FloorCellSubclass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APRCell> WallCellSubclass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APRCell> ExitCellSubclass;
	
	// this is playable size. Walls are not included in here
	UPROPERTY(EditAnywhere)
	FVector2DInt Size{7, 7};

	// corners cannot be exits
	UPROPERTY(EditAnywhere)
	FVector2DInt ExitPos{1, 4};
	
	UPROPERTY(EditAnywhere)
	TArray<FCongaData> CongasInitData;
};
