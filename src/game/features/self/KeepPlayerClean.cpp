#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class KeepPlayerClean : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().ClearDamage();
		}
	};

	static KeepPlayerClean _KeepPlayerClean{"keepplayerclean", "保持清洁", "使玩家保持干净，避免沾染血液、污垢和水。"};
}