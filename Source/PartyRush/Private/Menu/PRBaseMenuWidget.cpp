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
	if (MenusRowName == "") return;
	FMenusData* FoundRow = MenusDT->FindRow<FMenusData>(MenusRowName, "UPRBaseMenuWidget::Init");
	if (!FoundRow) return;
	MapSubmenusData = FoundRow->MapMenusData;
}

TSubclassOf<UPRBaseMenuWidget> UPRBaseMenuWidget::GetPopupWidget(FName PopupRowName, UDataTable* PopupDT/* = nullptr */ , FName MenusDataRowName/* = "Popups"*/) const
{
	// try to read data from table
	if (!IsValid(PopupDT))
	{
		if (!IsValid(MenusDT)) return nullptr;
		PopupDT = MenusDT;
	}
	if (MenusDataRowName == "") return nullptr;
	FMenusData* FoundRow = PopupDT->FindRow<FMenusData>(MenusDataRowName, "UPRBaseMenuWidget::GetPopupWidget");
	if (!FoundRow) return nullptr;
	return *(FoundRow->MapMenusData.Find(PopupRowName));
}
