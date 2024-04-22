// Fill out your copyright notice in the Description page of Project Settings.
// ItemData
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon     UMETA(DisplayName = "Weapon"),
	Equipment  UMETA(DisplayName = "Equipment")
};

USTRUCT(BlueprintType)
struct FItemStat : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StatName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
	
};

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemStat> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InitialQuantity;
	
};

//https://forums.unrealengine.com/t/data-tables-and-structures/604557