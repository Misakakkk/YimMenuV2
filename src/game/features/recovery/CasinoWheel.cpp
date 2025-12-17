#include "core/commands/Command.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class NoLuckyWheelCooldown : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetInt("MPX_LUCKY_WHEEL_NUM_SPIN", 0);
			*ScriptGlobal(262145).At(26765).As<int*>() = 1;
			*ScriptGlobal(262145).At(26766).As<int*>() = 1;
		}
	};

	static NoLuckyWheelCooldown _NoLuckyWheelCooldown{"noluckywheelcooldown", "幸运轮盘无冷却", "移除幸运轮盘的冷却，谨慎使用"};
}