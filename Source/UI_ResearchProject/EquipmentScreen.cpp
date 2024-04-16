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
}

void UEquipmentScreen::HandleNavigationChanged()
{
	UpdateLocalInventory();
}

void UEquipmentScreen::SelectItem(int ID)
{
	CurrentItem = ID;
}

void UEquipmentScreen::ChangeInventory()
{
	if(CurrentItem != -1 && CurrentSlot != -1)
	{
		
	}
}

void UEquipmentScreen::SelectSlot(int ID)
{
	CurrentSlot = ID;
}
