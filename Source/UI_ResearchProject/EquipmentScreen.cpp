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

// need to move to character manager
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

	//CurrentItemData = FItemData();
	//CurrentItemStats = "";

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
			//UE_LOG(LogTemp, Warning, TEXT("Update weapon"));
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
			//UE_LOG(LogTemp, Warning, TEXT("Update Item"));
		}
		UpdateLocalInventory();
	}
}

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

// current slot
// is it a weapon
// is the quantity 0
// is the character 0
// is it equiping


void UEquipmentScreen::SelectSlot(int ID)
{
	CurrentSlot = ID;
	ChangeCurrentItem(CurrentSlotData, CurrentSlotStats, ID);
	IsEquipping = false;
	FilterBy = ID > 1 ? EItemType::Equipment : EItemType::Weapon;
	UpdateLocalInventory();
}

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










