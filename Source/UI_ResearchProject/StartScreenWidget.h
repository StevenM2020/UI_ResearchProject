// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMainMenuWidget.h"
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
};
