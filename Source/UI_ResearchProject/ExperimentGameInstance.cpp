// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperimentGameInstance.h"

void UExperimentGameInstance::Init()
{
	Super::Init();

	// Create a new instance of the data controlling classes
	ExperimentSession = NewObject<UExperimentSession>(this, UExperimentSession::StaticClass());
	EquipmentManager = NewObject<UEquipmentManager>(this, UEquipmentManager::StaticClass());
	CharacterManager = NewObject<UCharacterManager>(this, UCharacterManager::StaticClass());
	// should add some code to check others
	if (ExperimentSession)
	{
		// session worked
	}

	EquipmentManager->InitializeInventoryFromDataTable(ItemDataTable);
	CharacterManager->InitializeFromDataTable(CharacterDataTable);
}
