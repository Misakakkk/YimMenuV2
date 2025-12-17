#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class ClearDamage : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPed().ClearDamage();
		}
	};

	static ClearDamage _ClearDamage{"cleardamage", "清除自身", "清除你身上的所有污垢和血迹。"};
}