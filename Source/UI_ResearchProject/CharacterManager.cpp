// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterManager.h"

bool UCharacterManager::AddWeaponToCharacter(int CharacterID, int WeaponID)
{
	return false;
}

int UCharacterManager::AddWeaponToCharacter(int CharacterID, int WeaponID, int WeaponSlot)
{
	if(!Characters[CharacterID].Weapons[WeaponSlot])
		return -2;
	int swap = Characters[CharacterID].Weapons[WeaponSlot];
	Characters[CharacterID].Weapons[WeaponSlot] = WeaponID;
	return swap;
}

bool UCharacterManager::AddItemToCharacter(int CharacterID, int ItemID)
{
	return false;
}

int UCharacterManager::AddItemToCharacter(int CharacterID, int ItemID, int ItemSlot)
{
	if(!Characters[CharacterID].Items[ItemSlot])
		return -2;
	int swap = Characters[CharacterID].Items[ItemSlot];
	Characters[CharacterID].Items[ItemSlot] = ItemID;
	return swap;
}

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
