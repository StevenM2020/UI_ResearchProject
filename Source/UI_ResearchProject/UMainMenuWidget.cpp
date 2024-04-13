// Fill out your copyright notice in the Description page of Project Settings.


#include "UMainMenuWidget.h"

#include "DynamicMesh/DynamicMesh3.h"

void UUMainMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(ExperimentGameInstance->ExperimentSession->IsSessionRunning() && ExperimentGameInstance->ExperimentSession->GetTotalTime() >= MaxTotalTime)
	{
		ExperimentGameInstance->ExperimentSession->EndSession();
		Navigate(0,2);
	}
	
}

void UUMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());

	// Optional: Check if the cast was successful
	if (!ExperimentGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExperimentGameInstance is not valid or not of the expected type"));
	}

	MaxTotalTime = ExperimentGameInstance->ExperimentSession->GetMaxTime();
}

void UUMainMenuWidget::Navigate(int32 Level, int32 ActiveWidgetIndex)
{
	if (WidgetSwitchers.IsValidIndex(Level))
	{
		UWidgetSwitcher* TargetSwitcher = WidgetSwitchers[Level];
		if (TargetSwitcher && TargetSwitcher->GetWidgetAtIndex(ActiveWidgetIndex))
		{
			TargetSwitcher->SetActiveWidgetIndex(ActiveWidgetIndex);
			//TargetSwitcher->GetChildAt(ActiveWidgetIndex)->SetVisibility(ESlateVisibility::Hidden);
			//TargetSwitcher->GetChildAt(ActiveWidgetIndex)->SetVisibility(ESlateVisibility::Visible);

			//UExperimentGameInstance* ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());


			
			
			if (ExperimentGameInstance)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Broadcasting OnNavigationChanged."));
				ExperimentGameInstance->OnNavigationChanged.Broadcast();
				//UE_LOG(LogTemp, Warning, TEXT("Broadcasted OnNavigationChanged."));
			}
		}
	}
}
