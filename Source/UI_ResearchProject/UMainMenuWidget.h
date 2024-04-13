// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/WidgetSwitcher.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ExperimentGameInstance.h"
#include "UMainMenuWidget.generated.h"


/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UUMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;

private:
	UExperimentGameInstance* ExperimentGameInstance;
	float MaxTotalTime;
	
public:
	
	UPROPERTY(BlueprintReadWrite, Category = "Menus")
	TArray<UWidgetSwitcher*> WidgetSwitchers;
	
	UFUNCTION(BlueprintCallable, Category = "Nav")
	void Navigate(int32 Level, int32 ActiveWidgetIndex);

// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Nav")
// 	UButton* btnLobby;
// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Nav")
// 	UButton* btnInventory;
// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Nav")
// 	UButton* btnOverview;
// 	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category = "Nav")
// 	UButton* btnEquiptment;
//
//
//
//
// 	UFUNCTION()
// 	void OnLobbyClicked();
//
// 	UFUNCTION()
// 	void OnInventoryClicked();
//
// 	UFUNCTION()
// 	void OnOverviewClicked();
//
// 	UFUNCTION()
// 	void OnEquipmentClicked();
//
// protected:
// 	virtual void NativeConstruct() override;


	
};
