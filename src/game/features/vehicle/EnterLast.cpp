#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class EnterLastVehicle : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (auto last_veh = Self::GetPed().GetLastVehicle())
				Self::GetPed().SetInVehicle(last_veh);
		}
	};

	static EnterLastVehicle _EnterLastVehicle{"enterlastvehicle", "进入上一载具", "进入上一次您乘坐的载具"};
};