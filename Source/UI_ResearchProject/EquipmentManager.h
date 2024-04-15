
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

UCLASS()
class UI_RESEARCHPROJECT_API UEquipmentManager : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UDataTable* ItemDataTable;  // Reference to the data table containing item definitions.

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FItemInventoryEntry> Inventory;  // Dynamic inventory data.

	void AddItemToInventory(int32 ItemID, int32 Quantity);
	void RemoveItemFromInventory(int32 ItemID, int32 Quantity);

	void InitializeInventoryFromDataTable(UDataTable* DataTable);
};
