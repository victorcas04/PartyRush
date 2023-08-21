#pragma once
#include "CoreMinimal.h"
#include "Vector2DInt.h"
#include "Engine/DataTable.h"
#include "PRCongaInfo.generated.h"

#define CONGAMEMBER_SIZE 100

UENUM(BlueprintType)
enum class EPRCongaMovementType : uint8
{
	None, 
	Horizontal,
	Vertical,
	HorizontalAndVertical,
	MAX
};

USTRUCT(BlueprintType)
struct PARTYRUSH_API FCongaData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APRConga> CongaSubclass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APRCongaMember> CongaMemberSubclass;

	UPROPERTY(EditAnywhere)
	EPRCongaMovementType MovementType{EPRCongaMovementType::HorizontalAndVertical};
	
	UPROPERTY(EditAnywhere)
	TArray<FVector2DInt> CongaMembersPositions;

	UPROPERTY(EditAnywhere)
	bool bIsPlayerConga{false};
};
