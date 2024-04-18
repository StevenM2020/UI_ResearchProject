
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.h"
#include "EquipmentManager.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;  // Reference to Item Data Table

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;  // Dynamic quantity of the item
};

USTRUCT(BlueprintType)
struct FItemSummary
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	
};

UCLASS()
class UI_RESEARCHPROJECT_API UEquipmentManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UDataTable* ItemDataTable;  // Reference to the data table containing item definitions.

	TArray<FItemData> Inventory;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	//TArray<FItemInventoryEntry> Inventory;  // Dynamic inventory data.

	//void AddItemToInventory(int32 ItemID, int32 Quantity);
	//void RemoveItemFromInventory(int32 ItemID, int32 Quantity);

	//TArray<FItemSummary> GetItemList();

	FItemData GetItem(int ID);

	FString GetItemName(int ID);
	
	void InitializeInventoryFromDataTable(UDataTable* DataTable);

	TArray<FItemSummary> GetItemsSummary();
};
