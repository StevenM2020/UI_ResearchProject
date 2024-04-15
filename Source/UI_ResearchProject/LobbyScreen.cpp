// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyScreen.h"

void ULobbyScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CurrentTaskTime = ExperimentGameInstance->ExperimentSession->GetTaskTime();
	TotalTaskTime = ExperimentGameInstance->ExperimentSession->GetTotalTime();

	PB_Percent = 1- TotalTaskTime/MaxTotalTime;
	
}

void ULobbyScreen::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());
	
	if (!ExperimentGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExperimentGameInstance is not valid or not of the expected type"));
	}

	MaxTotalTime = ExperimentGameInstance->ExperimentSession->GetMaxTime();

	ExperimentGameInstance->OnNavigationChanged.AddUObject(this, &ULobbyScreen::HandleNavigationChanged);
}

void ULobbyScreen::FinishExperiment()
{
	ExperimentGameInstance->ExperimentSession->EndSession();
	MainMenuWidget->Navigate(0,2);
	// then end the experiment
}

void ULobbyScreen::NextTask()
{
	ExperimentGameInstance->ExperimentSession->EndTask();
}


void ULobbyScreen::HandleNavigationChanged()
{
	CharacterInfo = ExperimentGameInstance->CharacterManager->GetCharacterInfo(0);
	if (CharacterInfo.IsValid)
	{
		// Proceed with using CharacterInfo
	}
	else
	{
		// Handle the error: Invalid character ID
	}
	
}

