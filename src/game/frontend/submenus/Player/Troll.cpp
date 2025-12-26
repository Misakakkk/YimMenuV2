#include "Troll.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildTrollMenu()
	{
		auto menu = std::make_shared<Category>("Troll");

		auto general = std::make_shared<Group>("通用");
		auto bounty = std::make_shared<Group>("赏金", 1);
		auto vehicle = std::make_shared<Group>("载具");

		general->AddItem(std::make_shared<PlayerCommandItem>("sendsext"_J));
		general->AddItem(std::make_shared<PlayerCommandItem>("sendphantomcar"_J));
		general->AddItem(std::make_shared<PlayerCommandItem>("sendgooch"_J));
		general->AddItem(std::make_shared<PlayerCommandItem>("giveplayerallweapon"_J));

		bounty->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, "数量"));
		bounty->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, "匿名"));
		bounty->AddItem(std::make_shared<PlayerCommandItem>("setbounty"_J));

		vehicle->AddItem(std::make_shared<PlayerCommandItem>("deleteveh"_J));

		menu->AddItem(general);
		menu->AddItem(bounty);
		menu->AddItem(vehicle);

		return menu;
	}
}