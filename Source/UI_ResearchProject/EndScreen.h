// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMainMenuWidget.h"
#include "EndScreen.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UEndScreen : public UUserWidget
{






public:
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category = "Nav")
	void BackToStart();

	UPROPERTY(BlueprintReadWrite, Category = "Menus")
	UUMainMenuWidget *MainMenuWidget;
};
