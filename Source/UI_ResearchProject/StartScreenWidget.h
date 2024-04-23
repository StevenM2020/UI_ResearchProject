// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMainMenuWidget.h"
#include "ExperimentGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "StartScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UStartScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "StartScreen")
	void Start();

	UPROPERTY(BlueprintReadWrite, Category = "Menus")
	UUMainMenuWidget *MainMenuWidget;

	UExperimentGameInstance* ExperimentGameInstance;


	UFUNCTION(BlueprintCallable, Category = "StartScreen")
	void SetFilter(bool On);

	UFUNCTION(BlueprintCallable, Category = "StartScreen")
	void SetSearch(bool On);

	UFUNCTION(BlueprintCallable, Category = "StartScreen")
	void SetDoubleClick(bool On);
	
protected:
	virtual void NativeConstruct() override; 
	
};
