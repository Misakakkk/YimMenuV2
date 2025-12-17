#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class UnlimitedOxygen : LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			Self::GetPed().SetMaxTimeUnderwater(INT_MAX);
		}

		virtual void OnDisable() override
		{
			Self::GetPed().SetMaxTimeUnderwater(-1.0f); // default value
		}
	};

	static UnlimitedOxygen _UnlimitedOxygen{"unlimitedoxygen", "无限氧气", "让你能在水下停留而不会缺氧。"};
}