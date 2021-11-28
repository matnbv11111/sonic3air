/*
*	Part of the Oxygen Engine / Sonic 3 A.I.R. software distribution.
*	Copyright (C) 2017-2021 by Eukaryot
*
*	Published under the GNU GPLv3 open source software license, see license.txt
*	or https://www.gnu.org/licenses/gpl-3.0.en.html
*/

#pragma once

#include "sonic3air/menu/options/OptionsEntry.h"
#include "oxygen/application/audio/AudioCollection.h"

class ControllerSetupMenu;
class MenuBackground;


class OptionsMenu : public GameMenuBase
{
public:
	OptionsMenu(MenuBackground& menuBackground);
	~OptionsMenu();

	virtual BaseState getBaseState() const override;
	virtual void onFadeIn() override;
	virtual bool canBeRemoved() override;

	virtual void initialize() override;
	virtual void deinitialize() override;
	virtual void keyboard(const rmx::KeyboardEvent& ev) override;
	virtual void update(float timeElapsed) override;
	virtual void render() override;

	void onEnteredFromIngame();
	void removeControllerSetupMenu();

private:
	enum class State
	{
		INACTIVE,
		APPEAR,
		SHOW,
		FADE_TO_MENU
	};

private:
	void setupOptionEntry(option::Option optionId, SharedDatabase::Setting::Type setting);
	void setupOptionEntryBitmask(option::Option optionId, SharedDatabase::Setting::Type setting);
	void setupOptionEntryBool(option::Option optionId, bool* valuePointer);
	void setupOptionEntryInt(option::Option optionId, int* valuePointer);
	void setupOptionEntryEnum8(option::Option optionId, void* valuePointer);
	void setupOptionEntryPercent(option::Option optionId, float* valuePointer);

	void playSoundtest(const AudioCollection::AudioDefinition& audioDefinition);
	void refreshGamepadLists(bool forceUpdate = false);
	bool isTitleShown(int tabIndex, int line) const;
	void goBack();

private:
	MenuBackground* mMenuBackground = nullptr;
	ControllerSetupMenu* mControllerSetupMenu = nullptr;

	GameMenuEntries mTabMenuEntries;
	struct Tab
	{
		enum Id
		{
			MODS	 = 0,
			DISPLAY	 = 1,
			AUDIO	 = 2,
			VISUALS	 = 3,
			GAMEPLAY = 4,
			CONTROLS = 5,
			TWEAKS	 = 6,
			INFO	 = 7,
			_NUM
		};

		GameMenuEntries mMenuEntries;
		std::map<size_t, std::string> mSections;
		std::map<size_t, std::string> mTitles;
	};
	Tab mTabs[Tab::Id::_NUM];
	size_t mActiveTab = 0;
	float mActiveTabAnimated = 0.0f;
	GameMenuEntries* mActiveMenu = &mTabMenuEntries;

	std::vector<OptionEntry> mOptionEntries;
	std::vector<GameMenuEntries::Entry*> mUnlockedSecretsEntries[2];
	GameMenuEntries::Entry* mGamepadAssignmentEntries[2] = { nullptr };

	uint32 mLastGamepadsChangeCounter = 0;
	std::vector<const AudioCollection::AudioDefinition*> mSoundTestAudioDefinitions;
	const AudioCollection::AudioDefinition* mPlayingSoundTest = nullptr;

	State mState = State::INACTIVE;
	float mVisibility = 0.0f;
	GameMenuScrolling mScrolling;
};
