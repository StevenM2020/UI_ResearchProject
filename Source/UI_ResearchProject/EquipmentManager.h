
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
	int32 ItemID; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;  
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
	UDataTable* ItemDataTable; 

	TArray<FItemData> Inventory;

	FItemData GetItem(int ID);

	FString GetItemName(int ID);
	
	void InitializeInventoryFromDataTable(UDataTable* DataTable);

	TArray<FItemSummary> GetItemsSummary();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FItemSummary> GetFilteredItemsSummary(EItemType ItemType, int MinimumQuantity);

	void RemoveItem(int ID);
	void AddItem(int ID);
	bool IsWeapon(int ID);
	bool HasItem(int ID);
	
	TArray<FItemSummary> SearchInventory(const FString& SearchText, TArray<FItemSummary> ItemSummary);
};