//Experiment Game Instance

#pragma once

#include "CoreMinimal.h"
#include "CharacterManager.h"
#include "ExperimentSession.h"
#include "EquipmentManager.h"
#include "Engine/GameInstance.h"
#include "ExperimentGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UExperimentGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UExperimentSession* ExperimentSession;
	UEquipmentManager* EquipmentManager;
	UCharacterManager* CharacterManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UDataTable* CharacterDataTable;
	
	virtual void Init() override;

	DECLARE_MULTICAST_DELEGATE(FOnNavigationChanged)
	FOnNavigationChanged OnNavigationChanged;
};
