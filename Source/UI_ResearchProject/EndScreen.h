// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMainMenuWidget.h"
#include "ExperimentGameInstance.h"
#include "EndScreen.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UEndScreen : public UUserWidget
{

protected:
	virtual void NativeConstruct() override;  // Declare NativeConstruct for clarity and proper access
	virtual void NativeDestruct() override;



public:
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Nav")
	void BackToStart();

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void UpdateOnVisible();

	UPROPERTY(BlueprintReadWrite, Category = "Nav")
	UUMainMenuWidget *MainMenuWidget;

	UExperimentGameInstance* ExperimentGameInstance;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	int pin;

	void HandleNavigationChanged();
};
