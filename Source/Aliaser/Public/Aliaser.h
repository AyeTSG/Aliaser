// Aliaser - /Aliaser/Source/Public/Aliaser.h
// Copyright AyeTSG 2023-2024.

#pragma once

#include "CoreMinimal.h"
#include "AliaserSettings.h"
#include "Modules/ModuleInterface.h"
#include "ContentBrowserAliasDataSource.h"

/**
 * Declare our logging category
 */
DECLARE_LOG_CATEGORY_EXTERN(LogAliaser, All, All);

class FAliaser : public IModuleInterface
{
public:
	/**
	 * Holds the user-configured settings for Aliaser
	 */
	const UAliaserSettings* AliaserSettings = GetDefault<UAliaserSettings>();

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};