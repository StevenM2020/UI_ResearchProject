// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMainMenuWidget.h"
#include "LobbyScreen.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API ULobbyScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Nav")
	void FinishExperiment();

	UFUNCTION(BlueprintCallable, Category = "Time")
	void NextTask();
	
	UPROPERTY(BlueprintReadWrite, Category = "Menus")
	UUMainMenuWidget *MainMenuWidget;


	// Variables to hold time information
	UPROPERTY(BlueprintReadOnly, Category = "Experiment")
	float CurrentTaskTime;

	UPROPERTY(BlueprintReadOnly, Category = "Experiment")
	float TotalTaskTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experiment")
	float MaxTotalTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Experiment")
	float PB_Percent;
};
