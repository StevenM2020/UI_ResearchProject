// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExperimentGameInstance.h"
#include "OverviewScreen.generated.h"




/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UOverviewScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override; 

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experiment")
	FCharacterInfo CharacterInfo;
	UExperimentGameInstance* ExperimentGameInstance;
	void HandleNavigationChanged();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<FString> Names;

	int CurrentCharacterID = -1;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SwitchCharacter(int ID, bool Override);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCharInfo CurrentCharacterInfo;
};
