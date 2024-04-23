// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperimentSession.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

void UExperimentSession::SessionTick()
{
	TotalTime += TickRate;
	TaskTime += TickRate;
}

void UExperimentSession::StartNewSession()
{
	SessionRunning = true;
	SessionNumber = UKismetMathLibrary::RandomIntegerInRange(100000, 999999);
	UE_LOG(LogTemp, Warning, TEXT("Session Number set to: %d"), SessionNumber);

	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		World->GetTimerManager().SetTimer(SessionTimerHandle, this, &UExperimentSession::SessionTick, TickRate, true);
	}
	TotalTime = 0.0f;
	TaskTime = 0.0f;
	TaskTimes.Empty();
}

void UExperimentSession::EndSession()
{
	SessionRunning = false;

	EndTask();
	
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (World)
	{
		World->GetTimerManager().ClearTimer(SessionTimerHandle);
	}
	
	SaveData();

	// clear the features
	FeaturesOn.Empty();
	TotalTime = 0.0f;
	TaskTime = 0.0f;
	TaskTimes.Empty();
}

void UExperimentSession::AddFeature(FString Feature, bool On)
{
	FeaturesOn.Add(Feature, On);
}

void UExperimentSession::EndTask()
{
	TaskTimes.Add(TaskTime);
	TaskTime = 0;
}

bool UExperimentSession::IsFeatureOn(FString Feature)
{
	Feature = Feature.ToLower();
	bool* isOnPtr = FeaturesOn.Find(Feature);
	return (isOnPtr != nullptr) ? *isOnPtr : false;
}

int UExperimentSession::GetSessionNumber()
{
	return SessionNumber;
}

float UExperimentSession::GetTaskTime()
{
	return TaskTime;
}

float UExperimentSession::GetTotalTime()
{
	return TotalTime;
}

float UExperimentSession::GetMaxTime()
{
	return MaxSessionTime;
}

void UExperimentSession::SetMaxTime(float MaxTime)
{
	MaxSessionTime = MaxTime;
}

bool UExperimentSession::IsSessionRunning()
{
	return SessionRunning;
}

void UExperimentSession::SetFeature(FString Name, bool On)
{
	Name = Name.ToLower();
	FeaturesOn.FindOrAdd(Name) = On;
}

void UExperimentSession::SaveData()
{
	// Construct a filename with the session number
	FString FileName = FString::Printf(TEXT("Session_%d.txt"), SessionNumber);
	FString SavePath = FPaths::ProjectDir() + TEXT("Saved/Sessions/") + FileName;

	// String to hold all the data
	FString OutputString;

	// Append session info
	OutputString += FString::Printf(TEXT("Session Number: %d\n"), SessionNumber);
	OutputString += FString::Printf(TEXT("Total Time: %f seconds\n"), TotalTime);

	// Append features info
	 OutputString += TEXT("Features On:\n");
	 for (const TPair<FString, bool>& Feature : FeaturesOn)
	 {
	 	OutputString += FString::Printf(TEXT("%s: %s\n"), *Feature.Key, Feature.Value ? TEXT("True") : TEXT("False"));
	 }

	// OutputString += TEXT("Features On:\n");
	// OutputString += FString::Printf(TEXT("Filter: %s\n"), UXFeatures.Filter ? TEXT("True") : TEXT("False"));
	// OutputString += FString::Printf(TEXT("Search: %s\n"), UXFeatures.Search ? TEXT("True") : TEXT("False"));
	
	// Append task times
	OutputString += TEXT("Task Times:\n");
	for (float Time : TaskTimes)
	{
		OutputString += FString::Printf(TEXT("%f\n"), Time);
	}

	// Save the string to a file
	if (!FFileHelper::SaveStringToFile(OutputString, *SavePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save session data to %s"), *SavePath);
	}
}
