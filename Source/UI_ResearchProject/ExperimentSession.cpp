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
	if (TaskTimes.IsValidIndex(0) || TaskTimes.Num() == 0)
	{
		TaskTimes.Add(TaskTime); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EndTask(), TaskTimes array error"));
	}
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

void UExperimentSession::SetWorld(UWorld* NewWorld)
{
	World = NewWorld;
}

void UExperimentSession::SaveData()
{
	// make file name and path
	FString FileName = FString::Printf(TEXT("Session_%d.txt"), SessionNumber);
	FString SavePath = FPaths::ProjectDir() + TEXT("Saved/Sessions/") + FileName;

	// Create the string to print
	FString OutputString;
	OutputString += FString::Printf(TEXT("Session Number: %d\n"), SessionNumber);
	OutputString += FString::Printf(TEXT("Total Time: %f seconds\n"), TotalTime);
	
	 OutputString += TEXT("Features On:\n");
	 for (const TPair<FString, bool>& Feature : FeaturesOn)
	 {
	 	OutputString += FString::Printf(TEXT("%s: %s\n"), *Feature.Key, Feature.Value ? TEXT("True") : TEXT("False"));
	 }
	
	OutputString += TEXT("Task Times:\n");
	for (float Time : TaskTimes)
	{
		OutputString += FString::Printf(TEXT("%f\n"), Time);
	}

	// print file
	if (!FFileHelper::SaveStringToFile(OutputString, *SavePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to save session data to %s"), *SavePath);
	}
}

UExperimentSession::~UExperimentSession()
{
	UE_LOG(LogTemp, Warning, TEXT("UExperimentSession is being destroyed"));
}
