// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TimerManager.h"
#include "ExperimentSession.generated.h"

/**
 * 
 */



USTRUCT(BlueprintType)
struct FFeatures
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Filter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Search;
	
};
UCLASS()
class UI_RESEARCHPROJECT_API UExperimentSession : public UObject
{
	GENERATED_BODY()

private:
 	int SessionNumber;

	TArray<float> TaskTimes;

	FFeatures UXFeatures;

	TMap<FString, bool> FeaturesOn;
	
	float TotalTime;

	float TaskTime;

	float MaxSessionTime = 200;

	float TickRate = 0.01;

	bool SessionRunning;
	
	FTimerHandle SessionTimerHandle;
	void SessionTick();
	void SaveData();

public:
	void StartNewSession();
	void EndSession();
	void AddFeature(FString Feature, bool On);
	void EndTask();
	bool IsFeatureOn(FString Feature);
	int	GetSessionNumber();
	float GetTaskTime();
	float GetTotalTime();
	float GetMaxTime();
	void SetMaxTime(float MaxTime);
	bool IsSessionRunning();
	void SetFeature(FString Name, bool On);
};

