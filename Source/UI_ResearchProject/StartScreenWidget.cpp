// Fill out your copyright notice in the Description page of Project Settings.


#include "StartScreenWidget.h"

void UStartScreenWidget::Start()
{
	ExperimentGameInstance->ExperimentSession->StartNewSession();
	MainMenuWidget->Navigate(0,1);
}

void UStartScreenWidget::SetFilter(bool On)
{
	ExperimentGameInstance->ExperimentSession->SetFeature("filter", On);
}

void UStartScreenWidget::SetSearch(bool On)
{
	ExperimentGameInstance->ExperimentSession->SetFeature("Search", On);
}

void UStartScreenWidget::SetDoubleClick(bool On)
{
	ExperimentGameInstance->ExperimentSession->SetFeature("double click", On);
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

	ExperimentGameInstance->ExperimentSession->SetFeature("filter", false);
	ExperimentGameInstance->ExperimentSession->SetFeature("search", false);
	ExperimentGameInstance->ExperimentSession->SetFeature("double click", false);
}
