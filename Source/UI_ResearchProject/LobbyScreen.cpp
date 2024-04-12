// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyScreen.h"

void ULobbyScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	CurrentTaskTime += InDeltaTime;
	TotalTaskTime += InDeltaTime;

	PB_Percent = 1- TotalTaskTime/MaxTotalTime;
}

void ULobbyScreen::FinishExperiment()
{
	MainMenuWidget->Navigate(0,2);

	// then end the experiment
}

void ULobbyScreen::NextTask()
{
	CurrentTaskTime = 0;

	// save the information
}
