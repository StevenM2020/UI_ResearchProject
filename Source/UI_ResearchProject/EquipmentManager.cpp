// EquipmentManager

#include "EquipmentManager.h"

#include "IDetailTreeNode.h"


FItemData UEquipmentManager::GetItem(int ID)
{
	return Inventory[ID];
}

FString UEquipmentManager::GetItemName(int ID)
{
	if (ID < 0) {
		UE_LOG(LogTemp, Error, TEXT("Attempted to get item name with invalid ID: %d"), ID);
		return FString(); 
	}

	for (const FItemData& Item : Inventory)
	{
		if (Item.ID == ID)
		{
			return Item.ItemName;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Item with ID %d not found in the inventory."), ID);
	return FString();
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

TArray<FItemSummary> UEquipmentManager::GetItemsSummary()
{
	TArray<FItemSummary> ItemsSummary;
	for (FItemData Item : Inventory)
	{
		FItemSummary ItemSummary;
		ItemSummary.ID = Item.ID;
		ItemSummary.Name = Item.ItemName;
		ItemsSummary.Add(ItemSummary);
	}
	return ItemsSummary;
}

TArray<FItemSummary> UEquipmentManager::GetFilteredItemsSummary(EItemType ItemType, int MinimumQuantity)
{
	TArray<FItemSummary> FilteredItems;
	for (const FItemData& Item : Inventory)
		{
		if (Item.ItemType == ItemType && Item.Quantity >= MinimumQuantity)
		{
			FItemSummary Summary;
			Summary.ID = Item.ID;
			Summary.Name = Item.ItemName;
			FilteredItems.Add(Summary);
		}
		}
	return FilteredItems;
}

void UEquipmentManager::RemoveItem(int ID)
{
	if(Inventory[ID].Quantity > 0)
		Inventory[ID].Quantity--;
}

void UEquipmentManager::AddItem(int ID)
{
	Inventory[ID].Quantity++;
}

bool UEquipmentManager::IsWeapon(int ID)
{
	return Inventory[ID].ItemType == EItemType::Weapon;
}

bool UEquipmentManager::HasItem(int ID)
{
	return Inventory[ID].Quantity > 0;
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

TArray<FItemSummary> UEquipmentManager::SearchInventory(const FString& SearchText, TArray<FItemSummary> ItemSummary)
{
	TArray<FItemSummary> FilteredInventory;
	for (const FItemSummary& Item : ItemSummary)
	{
		if (Item.Name.Contains(SearchText, ESearchCase::IgnoreCase, ESearchDir::FromStart))
		{
			FilteredInventory.Add(Item);
		}
	}
	return FilteredInventory;
}

