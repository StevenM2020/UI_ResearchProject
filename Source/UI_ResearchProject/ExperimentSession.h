// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExperimentSession.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UExperimentSession : public UObject
{
	GENERATED_BODY()

private:
 	int SessionNumber;

	TArray<float> TaskTimes;

	TMap<FString, bool> FeaturesOn;
	
	float TotalTime;


public:
	void StartNewSession();
	void EndSession(float NewTotalTime);
	void AddFeature(FString Feature, bool On);
	void EndTask(float Time);
	bool IsFeatureOn(FString Feature);
	int	GetSessionNumber();
};

