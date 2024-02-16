#include "PRBaseMenuWidget.h"
#include "Kismet/GameplayStatics.h"

void UPRBaseMenuWidget::CustomAddToViewport(int32 ZOrder)
{
	AddToViewport(ZOrder);
	/*
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!IsValid(PController)) return;
	SetUserFocus(PController);
	*/
}

void UPRBaseMenuWidget::Init()
{
	// try to read data from table
	if (!IsValid(MenusDT)) return;
	if (DT_RowName == "") return;
	FMenusData* FoundRow = MenusDT->FindRow<FMenusData>(DT_RowName, "UPRBaseMenuWidget::Init");
	if (!FoundRow) return;
	MapSubmenusData = FoundRow->MapMenusData;
}
