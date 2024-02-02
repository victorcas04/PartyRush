#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PRMenusInfo.generated.h"

class UPRBaseMenuWidget;

USTRUCT(BlueprintType)
struct PARTYRUSH_API FMenusData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<FName, TSubclassOf<UPRBaseMenuWidget>> MapMenusData;
};
