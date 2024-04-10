// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperimentSession.h"
#include "Kismet/KismetMathLibrary.h"

void UExperimentSession::StartNewSession()
{
	SessionNumber = UKismetMathLibrary::RandomIntegerInRange(1, 999999);

	TotalTime = 0.0f;

	TaskTimes.Empty();
}

void UExperimentSession::EndSession(float NewTotalTime)
{
	TotalTime = NewTotalTime;
	
	// saves everything to file
}

void UExperimentSession::AddFeature(FString Feature, bool On)
{
	FeaturesOn.Add(Feature, On);
}

void UExperimentSession::EndTask(float Time)
{
	TaskTimes.Add(Time);
}

bool UExperimentSession::IsFeatureOn(FString Feature)
{
	return FeaturesOn.Contains(Feature);
}

int UExperimentSession::GetSessionNumber()
{
	return SessionNumber;
}
