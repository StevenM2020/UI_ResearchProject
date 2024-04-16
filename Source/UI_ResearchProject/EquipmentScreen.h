// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExperimentGameInstance.h"
#include "EquipmentScreen.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UEquipmentScreen : public UUserWidget
{
	GENERATED_BODY()


protected:
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;  // Declare NativeConstruct for clarity and proper access


	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experiment")
	FCharacterInfo CharacterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCharInfo CurrentCharacterInfo;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void UpdateLocalInventory();

	void HandleNavigationChanged();

	UExperimentGameInstance* ExperimentGameInstance;

	int CurrentCharacterID = 0;

	int CurrentSlot = -1;

	int CurrentItem = -1;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SelectItem(int ID);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void ChangeInventory();

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SelectSlot(int ID);
};
