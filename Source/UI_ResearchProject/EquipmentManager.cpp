// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentManager.h"


void UEquipmentManager::InitializeInventoryFromDataTable(UDataTable* DataTable)
{

	if (!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Passed a null DataTable to EquipmentManager."));
		return;  // Exit if DataTable is null to prevent further errors.
	}
	UE_LOG(LogTemp, Error, TEXT("Worked."));
	ItemDataTable = DataTable;
	if (!ItemDataTable) return;
	// Loop through all rows in the Item Data Table
	for (const auto& RowPair : ItemDataTable->GetRowMap())
	{
		FItemData* Item = (FItemData*)RowPair.Value;
		if (Item)
		{
			FItemInventoryEntry NewEntry;
			NewEntry.ItemID = Item->ID;
			NewEntry.Quantity = Item->InitialQuantity;  // Set initial quantity from data table
			Inventory.Add(NewEntry);  // Add to the inventory
		}
	}
}
