#include "core/commands/BoolCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{

	class FreeChangeAppearance : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		Tunable m_CharacterAppearanceCharge{"CHARACTER_APPEARANCE_CHARGE"_J};

		virtual void OnEnable() override
		{
			if (m_CharacterAppearanceCharge.IsReady())
				m_CharacterAppearanceCharge.Set(0);
		}

		virtual void OnDisable() override
		{
			if (m_CharacterAppearanceCharge.IsReady())
				m_CharacterAppearanceCharge.Set(100000);
		}
	};

	static FreeChangeAppearance _FreeChangeAppearance{"freechangeappearance", "外貌改变免费", "允许玩家免费更改外貌"};
}