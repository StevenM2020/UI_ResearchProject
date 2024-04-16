// EquipmentManager

#include "EquipmentManager.h"

#include "IDetailTreeNode.h"


FString UEquipmentManager::GetItemName(int ID)
{
	FString Name = "";
	for (FItemData Item : Inventory)
	{
		if(Item.ID == ID)
			Name = Item.ItemName;
	}
	return Name;
}

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
	
	int count = 0;
	for (const TPair<FName, uint8*>& RowPair : ItemDataTable->GetRowMap())
	{
		const FItemData* ItemInfo = ItemDataTable->FindRow<FItemData>(RowPair.Key, TEXT("GetRow Context"), true);
		if (ItemInfo)
		{
			Inventory.Add(*ItemInfo);
			Inventory[count].ID = count;
			count++;
		}
	}
	
}


// Loop through all rows in the Item Data Table
// for (const auto& RowPair : ItemDataTable->GetRowMap())
// {
// 	FItemData* Item = (FItemData*)RowPair.Value;
// 	if (Item)
// 	{
// 		FItemInventoryEntry NewEntry;
// 		NewEntry.ItemID = Item->ID;
// 		NewEntry.Quantity = Item->InitialQuantity;  // Set initial quantity from data table
// 		Inventory.Add(NewEntry);  // Add to the inventory
// 	}
// }



