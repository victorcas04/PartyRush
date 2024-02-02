#include "PRBaseMenuWidget.h"

void UPRBaseMenuWidget::Init()
{
	// try to read data from table
	if (!IsValid(MenusDT)) return;
	if (DT_RowName == "") return;
	FMenusData* FoundRow = MenusDT->FindRow<FMenusData>(DT_RowName, "UPRBaseMenuWidget::Init");
	if (!FoundRow) return;
	MapSubmenusData = FoundRow->MapMenusData;
}
