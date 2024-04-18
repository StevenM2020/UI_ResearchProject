// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterManager.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = TEXT("Character");
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Weapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> Items;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsValid = false;

	FCharacterInfo()
	{
		Weapons.Init(-1, 2);
		Items.Init(-1, 4);
		IsValid = true;
	}
};

USTRUCT(BlueprintType)
struct FCharInfo 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Weapon1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Weapon2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Item4;
	
};


UCLASS()
class UI_RESEARCHPROJECT_API UCharacterManager : public UObject
{
	GENERATED_BODY()
private:
	TArray<FCharacterInfo> Characters;
	int CurrentCharacterID = 0;
public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UDataTable* CharacterDataTable;
	
	bool AddWeaponToCharacter(int CharacterID, int WeaponID);
	void AddWeaponToCharacter(int CharacterID, int WeaponID, int WeaponSlot);

	bool AddItemToCharacter(int CharacterID, int ItemID);
	void AddItemToCharacter(int CharacterID, int ItemID, int ItemSlot); // returns whats in the spot

	void InitializeFromDataTable(UDataTable* DataTable);

	int GetCurrentCharacterID();
	bool SetCurrentCharacterID(int CharID);
	
	TArray<FString> GetCharacterNames();

	FCharacterInfo GetCharacterInfo(int CharID);
};
