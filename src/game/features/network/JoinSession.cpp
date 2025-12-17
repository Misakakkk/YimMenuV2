#include "core/commands/Command.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Network.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_JoinTypes = {
	    {static_cast<int>(Network::JoinType::JOIN_PUBLIC), "公开战局"},
	    {static_cast<int>(Network::JoinType::NEW_PUBLIC), "新公开战局"},
	    {static_cast<int>(Network::JoinType::SC_TV), "SCTV观战"},
	    {static_cast<int>(Network::JoinType::CREW), "帮会战局"},
	    {static_cast<int>(Network::JoinType::JOIN_CREW), "加入帮会"},
	    {static_cast<int>(Network::JoinType::CLOSED_CREW), "非公开帮会战局"},
	    {static_cast<int>(Network::JoinType::CLOSED_FRIENDS), "非公开好友战局"},
	    {static_cast<int>(Network::JoinType::FIND_FRIEND), "加入好友"},
	    {static_cast<int>(Network::JoinType::INVITE_ONLY), "仅限邀请战局"},
	    {static_cast<int>(Network::JoinType::SOLO), "单人战局"},
	};

	static ListCommand _JoinType{"joinsessiontype", "Join Session Type", "The session type to join", g_JoinTypes, static_cast<int>(Network::JoinType::JOIN_PUBLIC)};

	class JoinSession : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Network::LaunchJoinType(static_cast<Network::JoinType>(_JoinType.GetState()));
		}
	};
	static JoinSession _JoinSession{"joinsession", "Join Session", "加入指定的战局类型"};


}