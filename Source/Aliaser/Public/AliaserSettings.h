// Aliaser - /Aliaser/Source/Public/AliaserSettings.h
// Copyright AyeTSG 2023-2024.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "AliaserSettings.generated.h"

/***
 * Holds an aliaser entry
 */
USTRUCT(BlueprintType)
struct FAliserAliasEntry
{
	GENERATED_BODY()

public:
	/**
	 * Path to the asset being aliased
	 */
	UPROPERTY(Category = "Aliaser", Config, EditAnywhere)
	FSoftObjectPath AssetPath;

	/**
	 * Where should the alias be put in the content browser?
	 */
	UPROPERTY(Category = "Aliaser", Config, EditAnywhere)
	FName AliasPath;
};

/**
 * Holds the primary settings for Aliaser
 */
UCLASS(Config=Editor, DefaultConfig)
class UAliaserSettings : public UObject
{
	GENERATED_BODY()

public:
	/** 
	 * Default constructor
	 */
	UAliaserSettings();

	/**
	 * List of assets, then aliases
	 */
	UPROPERTY(Category = "Aliaser", Config, EditAnywhere)
	TArray<FAliserAliasEntry> AliasEntries;
};