// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentScreen.h"

void UEquipmentScreen::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());

	if (!ExperimentGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExperimentGameInstance is not valid or not of the expected type"));
	}
	
	ExperimentGameInstance->OnNavigationChanged.AddUObject(this, &UEquipmentScreen::HandleNavigationChanged);

	CharacterInfo = ExperimentGameInstance->CharacterManager->GetCharacterInfo(0);

	CurrentCharacterID = ExperimentGameInstance->CharacterManager->GetCurrentCharacterID();
	
}

// Updates the objects showing the local character information and equipment information.
void UEquipmentScreen::UpdateLocalInventory()
{
	CharacterInfo = ExperimentGameInstance->CharacterManager->GetCharacterInfo(CurrentCharacterID);

	CurrentCharacterInfo.Weapon1 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Weapons[0]);
	CurrentCharacterInfo.Weapon2 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Weapons[1]);
	CurrentCharacterInfo.Item1 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[0]);
	CurrentCharacterInfo.Item2 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[1]);
	CurrentCharacterInfo.Item3 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[2]);
	CurrentCharacterInfo.Item4 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[3]);
	
	if(FilterOn)
	{
		Inventory = ExperimentGameInstance->EquipmentManager->GetFilteredItemsSummary(FilterBy, 1);
	}else
	{
		Inventory = ExperimentGameInstance->EquipmentManager->GetItemsSummary();	
	}
	CurrentItem = -1;

	if(!SearchText.IsEmpty())
	{
		Inventory = ExperimentGameInstance->EquipmentManager->SearchInventory(SearchText, Inventory);
	}

	OnInventoryUpdated();
}

void UEquipmentScreen::HandleNavigationChanged()
{
	CurrentCharacterID = ExperimentGameInstance->CharacterManager->GetCurrentCharacterID();
	UE_LOG(LogTemp, Warning, TEXT("NAV CHANGE"));
	CurrentSlot = -1;
	UpdateLocalInventory();
}

void UEquipmentScreen::SelectItem(int ID)
{
	CurrentItem = ID;
	ChangeCurrentItem(CurrentItemData, CurrentItemStats, ID);
	IsEquipping = true;
}

// Function called by equip button to move an item from the equipment to the character.
void UEquipmentScreen::Equip()
{
	if(CurrentItem >= 0 && CurrentSlot >= 0)
	{
		const bool IsWeapon = ExperimentGameInstance->EquipmentManager->IsWeapon(CurrentItem);
		if(CurrentSlot < 2 && IsWeapon)
		{
			if(ExperimentGameInstance->EquipmentManager->HasItem(CurrentItem))
			{
				ExperimentGameInstance->EquipmentManager->RemoveItem(CurrentItem);
				int temp = ExperimentGameInstance->CharacterManager->AddWeaponToCharacter(CurrentItem,CurrentSlot);
				if(temp >= 0)
					ExperimentGameInstance->EquipmentManager->AddItem(temp);
			}
		}
		else if(CurrentSlot > 1 && CurrentSlot < 6 && !IsWeapon)
		{
			if(ExperimentGameInstance->EquipmentManager->HasItem(CurrentItem))
			{
				ExperimentGameInstance->EquipmentManager->RemoveItem(CurrentItem);
				int temp = ExperimentGameInstance->CharacterManager->AddItemToCharacter(CurrentItem,CurrentSlot-2);
				if(temp >= 0)
					ExperimentGameInstance->EquipmentManager->AddItem(temp);
			}
		}
		ChangeCurrentItem(CurrentItemData, CurrentItemStats, CurrentItem);
		ChangeCurrentItem(CurrentSlotData, CurrentSlotStats, CurrentSlot);
		UpdateLocalInventory();
	}
}

// Moves an item from the character to the equipment manager.
void UEquipmentScreen::Unequip()
{
	if( CurrentSlot >= 0)
	{
		int ItemID = ExperimentGameInstance->CharacterManager->RemoveItemOrWeapon(CurrentSlot);
		if(ItemID >= 0)
		{
			ExperimentGameInstance->EquipmentManager->AddItem(ItemID);
			UpdateLocalInventory();
		}
	}
}

void UEquipmentScreen::SelectSlot(int ID)
{
	CurrentSlot = ID;
	ChangeCurrentItem(CurrentSlotData, CurrentSlotStats, ID);
	IsEquipping = false;
	FilterBy = ID > 1 ? EItemType::Equipment : EItemType::Weapon;
	UpdateLocalInventory();
}

// Updates item display info objects
void UEquipmentScreen::ChangeCurrentItem(FItemData& Data, FString& Stats, int ID)
{
	Data = ExperimentGameInstance->EquipmentManager->GetItem(ID);
	Data.Description = "Description: " + Data.Description;
	Stats = "Stats:\n";
	for (FItemStat Stat : Data.Stats)
	{
		Stats.Append(FString::Printf(TEXT("%s: %.1f\n"), *Stat.StatName, Stat.Value)); 
	}
}

bool UEquipmentScreen::CanFilter()
{
	return ExperimentGameInstance->ExperimentSession->IsFeatureOn("filter");
}
bool UEquipmentScreen::CanSearch()
{
	return ExperimentGameInstance->ExperimentSession->IsFeatureOn("search");
}
bool UEquipmentScreen::CanDoubleClick()
{
	return ExperimentGameInstance->ExperimentSession->IsFeatureOn("double click");
}

void UEquipmentScreen::SearchTextChanged(FString NewSearchText)
{
	SearchText = NewSearchText;
	UpdateLocalInventory();
}










