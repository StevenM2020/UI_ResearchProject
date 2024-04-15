// End Screen Code


#include "EndScreen.h"

void UEndScreen::BackToStart()
{
	MainMenuWidget->Navigate(0,0);
}

void UEndScreen::UpdateOnVisible()
{
	pin = ExperimentGameInstance->ExperimentSession->GetSessionNumber();
}

void UEndScreen::NativeConstruct()
{
	Super::NativeConstruct();
	
	ExperimentGameInstance = Cast<UExperimentGameInstance>(GetWorld()->GetGameInstance());
	
	if (!ExperimentGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExperimentGameInstance is not valid or not of the expected type"));
		return;
	}

	ExperimentGameInstance->OnNavigationChanged.AddUObject(this, &UEndScreen::HandleNavigationChanged);
	
}


void UEndScreen::NativeDestruct()
{
	
	if (ExperimentGameInstance)
	{
		ExperimentGameInstance->OnNavigationChanged.RemoveAll(this);
	}
	Super::NativeDestruct();
}

void UEndScreen::HandleNavigationChanged()
{
	// Refresh or update logic here
	pin = ExperimentGameInstance->ExperimentSession->GetSessionNumber();
}

