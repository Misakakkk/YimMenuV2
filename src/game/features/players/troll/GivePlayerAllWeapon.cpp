#include "game/commands/PlayerCommand.hpp"
#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/Weapons.hpp"


namespace YimMenu::Features
{
	class GivePlayerAllWeapon : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			for (auto weapon : g_WeaponHashes)
				player.GetPed().GiveWeapon(weapon);
		}
	};

	static GivePlayerAllWeapon _GivePlayerAllWeapon{"giveplayerallweapon", "给玩家所有武器", "给这名玩家所有武器"};
}