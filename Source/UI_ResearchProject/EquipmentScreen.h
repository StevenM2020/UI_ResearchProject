// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExperimentGameInstance.h"
#include "EquipmentScreen.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdatedDelegate);

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UEquipmentScreen : public UUserWidget
{
	GENERATED_BODY()


protected:
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override; 


	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experiment")
	FCharacterInfo CharacterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCharInfo CurrentCharacterInfo;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void UpdateLocalInventory();

	void HandleNavigationChanged();

	UExperimentGameInstance* ExperimentGameInstance;

	int CurrentCharacterID = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int CurrentSlot = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int CurrentItem = -1;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SelectItem(int ID);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void Equip();
	
	UFUNCTION(BlueprintCallable, Category = "Character")
	void Unequip();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SelectSlot(int ID);
	
	UFUNCTION(BlueprintImplementableEvent , Category = "Inventory")
	void OnInventoryUpdated();

	UFUNCTION(BlueprintCallable , Category = "Inventory")
	void ChangeCurrentItem(FItemData& Data, FString& Stats, int ID);

	UFUNCTION(BlueprintCallable , Category = "Session")
	bool CanFilter();

	UFUNCTION(BlueprintCallable , Category = "Session")
	bool CanSearch();
	
	UFUNCTION(BlueprintCallable , Category = "Session")
	bool CanDoubleClick();

	UFUNCTION(BlueprintCallable , Category = "Inventory")
	void SearchTextChanged(FString NewSearchText);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FItemData CurrentItemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FItemData CurrentSlotData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString CurrentItemStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString CurrentSlotStats;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<FItemSummary> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool IsEquipping = true;

	EItemType FilterBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool FilterOn;

	FString SearchText = "";
	
	
};
