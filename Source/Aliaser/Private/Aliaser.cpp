// Aliaser - /Aliaser/Source/Private/Aliaser.cpp
// Copyright AyeTSG 2023-2024.

#include "Aliaser.h"
#include "AliaserSettings.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "IContentBrowserDataModule.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"


/**
 * Define our localization namespace
 */
#define LOCTEXT_NAMESPACE "FAliaserModule"

/**
 * Define our logging category
 */
DEFINE_LOG_CATEGORY(LogAliaser);

/**
 * Define our data source
 */
TStrongObjectPtr<UContentBrowserAliasDataSource> AliaserDataSource;

void FAliaser::StartupModule()
{
	UE_LOG(LogAliaser, Log, TEXT("Aliaser module starting up"));

	/**
	 * Get the settings module
	 */
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		/**
		 * Register our settings page
		 */
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "Aliaser", INVTEXT("Aliaser"), INVTEXT("Configure the Aliaser plug-in"), GetMutableDefault<UAliaserSettings>());
		UE_LOG(LogAliaser, Log, TEXT("Registered settings \"Project -> Plugins -> Aliaser\""));
	}

	/**
	 * Initialize the Aliaser data source
	 */
	AliaserDataSource.Reset(NewObject<UContentBrowserAliasDataSource>(GetTransientPackage(), "AliaserData"));
	AliaserDataSource->Initialize();


	/**
	 * For each user-configured alias
	 */
	for (auto aliasEntry : AliaserSettings->AliasEntries)
	{
		/**
		 * Get the UObject of the asset
		 */
		UObject* Object = aliasEntry.AssetPath.TryLoad();

		/**
		 * Get the FAssetData of that UObject
		 */
		FAssetData ObjectData = FAssetData(Object, true);

		/**
		 * Register the alias within the data source
		 */
		AliaserDataSource->AddAlias(ObjectData, aliasEntry.AliasPath, false, true);
	}

	/**
	 * Debug: Logs aliases associated with this data source
	 */
	//AliaserDataSource->LogAliases();

	/**
	 * Get the content browser data system
	 * and enable the data source
	 */
	UE_LOG(LogAliaser, Log, TEXT("Enabling AliaserData data source"));
	UContentBrowserDataSubsystem* ContentBrowserData = GEditor->GetEditorSubsystem<UContentBrowserDataSubsystem>();
	ContentBrowserData->ActivateDataSource("AliaserData");
}

void FAliaser::ShutdownModule()
{
	UE_LOG(LogAliaser, Log, TEXT("Aliaser module shutting down"));

	/**
	 * Get the settings module
	 */
	ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
	if (SettingsModule != nullptr)
	{
		/**
		 * Deregister our settings page
		 */
		SettingsModule->UnregisterSettings("Project", "Plugins", "Aliaser");
		UE_LOG(LogAliaser, Log, TEXT("Dergistered settings \"Project -> Plugins -> Aliaser\""));
	}
}

/**
 * Undefine our localization namespace
 */
#undef LOCTEXT_NAMESPACE

/**
 * Implement FAliaser as the module class
 */
IMPLEMENT_GAME_MODULE(FAliaser, Aliaser);