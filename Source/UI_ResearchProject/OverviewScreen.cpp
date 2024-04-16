// Fill out your copyright notice in the Description page of Project Settings.


#include "OverviewScreen.h"

void UOverviewScreen::NativeConstruct()
{
	Super::NativeConstruct();

	ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());

	if (!ExperimentGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExperimentGameInstance is not valid or not of the expected type"));
	}
	
	Names = ExperimentGameInstance->CharacterManager->GetCharacterNames();
	
	ExperimentGameInstance->OnNavigationChanged.AddUObject(this, &UOverviewScreen::HandleNavigationChanged);

	CharacterInfo = ExperimentGameInstance->CharacterManager->GetCharacterInfo(CurrentCharacterID);

}

void UOverviewScreen::HandleNavigationChanged()
{
	SwitchCharacter(0);
}

void UOverviewScreen::SwitchCharacter(int ID)
{
	if(ID != CurrentCharacterID)
	{
		CurrentCharacterID = ID;
		ExperimentGameInstance->CharacterManager->SetCurrentCharacterID(ID);
		CharacterInfo = ExperimentGameInstance->CharacterManager->GetCharacterInfo(CurrentCharacterID);

		CurrentCharacterInfo.Weapon1 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Weapons[0]);
		CurrentCharacterInfo.Weapon2 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Weapons[1]);
		CurrentCharacterInfo.Item1 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[0]);
		CurrentCharacterInfo.Item2 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[1]);
		CurrentCharacterInfo.Item3 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[2]);
		CurrentCharacterInfo.Item4 = ExperimentGameInstance->EquipmentManager->GetItemName(CharacterInfo.Items[3]);
	}
}
