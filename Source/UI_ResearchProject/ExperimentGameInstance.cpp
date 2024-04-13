// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperimentGameInstance.h"

void UExperimentGameInstance::Init()
{
	Super::Init();

	// Create a new instance of the session class
	ExperimentSession = NewObject<UExperimentSession>(this, UExperimentSession::StaticClass());
    
	if (ExperimentSession)
	{
		// session worked
	}
}
