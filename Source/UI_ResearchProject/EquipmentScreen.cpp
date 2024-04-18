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

		Inventory = ExperimentGameInstance->EquipmentManager->GetItemsSummary();

		OnInventoryUpdated();
}

void UEquipmentScreen::HandleNavigationChanged()
{
	UpdateLocalInventory();
}

void UEquipmentScreen::SelectItem(int ID)
{
	CurrentItem = ID;
	CurrentItemData = ExperimentGameInstance->EquipmentManager->GetItem(ID);
	CurrentItemData.Description = "Description: " + CurrentItemData.Description;
	CurrentItemStats = "Stats:\n";
	for (FItemStat Stat : CurrentItemData.Stats)
	{
		CurrentItemStats.Append(FString::Printf(TEXT("%s: %f\n"), *Stat.StatName, Stat.Value)); 
	}
}

void UEquipmentScreen::ChangeInventory()
{
	if(CurrentItem != -1 && CurrentSlot != -1)
	{
		if(CurrentSlot < 2)
		{
			ExperimentGameInstance->CharacterManager->AddWeaponToCharacter(0,CurrentItem,CurrentSlot);
			UE_LOG(LogTemp, Warning, TEXT("Update weapon"));
		}
		if(CurrentSlot > 1)
		{
			ExperimentGameInstance->CharacterManager->AddItemToCharacter(0,CurrentItem,CurrentSlot-2);
			UE_LOG(LogTemp, Warning, TEXT("Update Item"));
		}
		UpdateLocalInventory();
	}
}

void UEquipmentScreen::SelectSlot(int ID)
{
	CurrentSlot = ID;
}








