// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"

int UCharacterManager::AddWeaponToCharacter(int WeaponID, int WeaponSlot)
{
	if(!Characters[CurrentCharacterID].Weapons.IsValidIndex(WeaponSlot))
		return -1;
	int swap = Characters[CurrentCharacterID].Weapons[WeaponSlot];
	Characters[CurrentCharacterID].Weapons[WeaponSlot] = WeaponID;
	UE_LOG(LogTemp, Warning, TEXT("Weapon"));
	return swap;
}


int UCharacterManager::AddItemToCharacter(int ItemID, int ItemSlot)
{
	//if(!Characters[CharacterID].Items.IsValidIndex(ItemSlot))
	//	return;
	int swap = Characters[CurrentCharacterID].Items[ItemSlot];
	Characters[CurrentCharacterID].Items[ItemSlot] = ItemID;
	UE_LOG(LogTemp, Warning, TEXT("Item"));
	return swap;
}

int UCharacterManager::RemoveItemOrWeapon(int Slot)
{
	int temp = -1;
	if(Slot < 2)
	{
		temp = Characters[CurrentCharacterID].Weapons[Slot];
		Characters[CurrentCharacterID].Weapons[Slot] = -1;
	}else
	{
		temp = Characters[CurrentCharacterID].Items[Slot - 2];
		Characters[CurrentCharacterID].Items[Slot - 2] = -1;
	}
	return temp;
}

// if(!Characters[CharacterID].Items[ItemSlot])
// 	return -2;
// int swap = Characters[CharacterID].Items[ItemSlot];
// Characters[CharacterID].Items[ItemSlot] = ItemID;
// return swap;
void UCharacterManager::InitializeFromDataTable(UDataTable* DataTable)
{
	CharacterDataTable = DataTable;
	if (!CharacterDataTable) return;
	
	CharacterDataTable = DataTable;
	if (!CharacterDataTable) return;

	// import the table into the array
	for (const auto& RowPair : CharacterDataTable->GetRowMap())
	{
		FCharacterInfo* CharInfo = (FCharacterInfo*)RowPair.Value;
		if (CharInfo)
		{
			Characters.Add(*CharInfo);
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("%d characters loaded from Data Table."), Characters.Num());
}

int UCharacterManager::GetCurrentCharacterID()
{
	return CurrentCharacterID;
}

bool UCharacterManager::SetCurrentCharacterID(int CharID)
{
	if(CharID >= 0 && CharID < Characters.Num())
	{
		CurrentCharacterID = CharID;
		UE_LOG(LogTemp, Log, TEXT("%d Character has been changed."), CurrentCharacterID);
		return true;
	}
	return false;
}

TArray<FString> UCharacterManager::GetCharacterNames()
{
	TArray<FString> CharArray;
	for (FCharacterInfo Character : Characters)
	{
		CharArray.Add(Character.Name);
	}
	return CharArray;
}

FCharacterInfo UCharacterManager::GetCharacterInfo(int CharID)
{
	if (CharID >= 0 && CharID < Characters.Num())
	{
		return Characters[CharID];
	}

	// return invalid character if no character
	FCharacterInfo InvalidCharacter;
	InvalidCharacter.IsValid = false;
	return InvalidCharacter;
}
