// Fill out your copyright notice in the Description page of Project Settings.


#include "StartScreenWidget.h"

void UStartScreenWidget::Start()
{
	ExperimentGameInstance->ExperimentSession->StartNewSession();
	MainMenuWidget->Navigate(0,1);
}

void UStartScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();


	ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());


	if (!ExperimentGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExperimentGameInstance is not valid or not of the expected type"));
		return;
	}

	
	
}