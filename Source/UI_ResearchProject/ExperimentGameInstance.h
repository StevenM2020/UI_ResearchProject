//Experiment Game Instance

#pragma once

#include "CoreMinimal.h"
#include "ExperimentSession.h"
#include "Engine/GameInstance.h"
#include "ExperimentGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UExperimentGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UExperimentSession* ExperimentSession;
	
	virtual void Init() override;

	DECLARE_MULTICAST_DELEGATE(FOnNavigationChanged)
	FOnNavigationChanged OnNavigationChanged;
};
