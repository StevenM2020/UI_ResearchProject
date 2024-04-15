// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS()
class UI_RESEARCHPROJECT_API UItem : public UObject
{
	GENERATED_BODY()


private:
	int ID;
	FString Name;
	FString Description;
	float Damage;
};
