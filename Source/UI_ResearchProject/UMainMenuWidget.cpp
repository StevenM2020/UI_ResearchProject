// Fill out your copyright notice in the Description page of Project Settings.


#include "UMainMenuWidget.h"

#include "DynamicMesh/DynamicMesh3.h"

void UUMainMenuWidget::Navigate(int32 Level, int32 ActiveWidgetIndex)
{
	if (WidgetSwitchers.IsValidIndex(Level))
	{
		UWidgetSwitcher* TargetSwitcher = WidgetSwitchers[Level];
		if (TargetSwitcher && TargetSwitcher->GetWidgetAtIndex(ActiveWidgetIndex))
		{
			TargetSwitcher->SetActiveWidgetIndex(ActiveWidgetIndex);
		}
	}
}

// void UUMainMenuWidget::OnLobbyClicked()
// {
// 	Navigate(1,0);
// 	UE_LOG(LogTemp, Warning, TEXT("Your message here."));
// }
//
// void UUMainMenuWidget::OnInventoryClicked()
// {
// 	Navigate(1, 1);
// }
//
// void UUMainMenuWidget::OnOverviewClicked()
// {
// 	Navigate(0, 2);
// }
//
// void UUMainMenuWidget::OnEquipmentClicked()
// {
// 	Navigate(1, 2);
// }
//
// void UUMainMenuWidget::NativeConstruct()
// {
// 	Super::NativeConstruct();
//
// 	if (btnLobby)
// 	{
// 		btnLobby->OnClicked.AddDynamic(this, &UUMainMenuWidget::OnLobbyClicked);
// 	}
//
// 	if (btnInventory)
// 	{
// 		btnInventory->OnClicked.AddDynamic(this, &UUMainMenuWidget::OnInventoryClicked);
// 	}
// 	if (btnEquiptment)
// 	{
// 		btnEquiptment->OnClicked.AddDynamic(this, &UUMainMenuWidget::OnEquipmentClicked);
// 	}
// 	if (btnOverview)
// 	{
// 		btnOverview->OnClicked.AddDynamic(this, &UUMainMenuWidget::OnOverviewClicked);
// 	}
// 	// Repeat for each button, binding to the appropriate handler...
// }