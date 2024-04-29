// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperimentGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UExperimentGameInstance::Init()
{
	Super::Init();

	if(ExperimentSession || EquipmentManager || CharacterManager)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("UExperimentGameInstance is creating data objects"));

	// Creates the objects. Used TStrongObjectPtr to stop them from being deleted.
	ExperimentSession = TStrongObjectPtr<UExperimentSession>(NewObject<UExperimentSession>(this, UExperimentSession::StaticClass()));
	EquipmentManager = TStrongObjectPtr<UEquipmentManager>(NewObject<UEquipmentManager>(this, UEquipmentManager::StaticClass()));
	CharacterManager = TStrongObjectPtr<UCharacterManager>(NewObject<UCharacterManager>(this, UCharacterManager::StaticClass()));

	ExperimentSession->SetWorld(GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull));
	EquipmentManager->InitializeInventoryFromDataTable(ItemDataTable);
	CharacterManager->InitializeFromDataTable(CharacterDataTable);
}

UExperimentGameInstance::~UExperimentGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("UExperimentGameInstance is being destroyed"));
}
