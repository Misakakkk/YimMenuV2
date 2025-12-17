#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	namespace DiamondCasinoHeist
	{
		static IntCommand _DiamondCasinoHeistCut1{"diamondcasinoheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut2{"diamondcasinoheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut3{"diamondcasinoheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut4{"diamondcasinoheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1973230).At(1497).At(736).At(92);

				*base.At(0, 1).As<int*>() = _DiamondCasinoHeistCut1.GetState();
				*base.At(1, 1).As<int*>() = _DiamondCasinoHeistCut2.GetState();
				*base.At(2, 1).As<int*>() = _DiamondCasinoHeistCut3.GetState();
				*base.At(3, 1).As<int*>() = _DiamondCasinoHeistCut4.GetState();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1977593);

				for (int i = 0; i <= 3; i++)
				{
					*base.At(i, 68).At(7).At(i, 1).As<int*>() = 1;
				}
			}
		};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistDifficulty = {
			{0, "普通模式"},
			{1, "困难模式"}
		};
		static ListCommand _DiamondCasinoHeistDifficulty{"diamondcasinoheistdifficulty", "难度", "Heist difficulty", diamondCasinoHeistDifficulty, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistPrimaryTarget = {
			{3, "钻石"},
			{1, "黄金"},
			{2, "艺术品"},
			{0, "现金"}
		};
		static ListCommand _DiamondCasinoHeistPrimaryTarget{"diamondcasinoheistprimarytarget", "主要目标", "Primary target", diamondCasinoHeistPrimaryTarget, 3};

		static ListCommand* _DiamondCasinoHeistGunmanPtr = nullptr;
		static ListCommand* _DiamondCasinoHeistApproachPtr = nullptr;

		static std::vector<std::vector<std::vector<std::pair<int, const char*>>>> diamondCasinoHeistWeapon = {
			{
				{{0, "MK II Shotgun Loadout"}, {1, "MK II Rifle Loadout"}},
				{{0, "MK II SMG Loadout"}, {1, "MK II Rifle Loadout"}},
				{{0, "MK II Shotgun Loadout"}, {1, "MK II Rifle Loadout"}}
			},
			{
				{{0, "Rifle Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Rifle Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Rifle Loadout"}, {1, "Shotgun Loadout"}}
			},
			{
				{{0, "Combat PDW Loadout"}, {1, "Rifle Loadout"}},
				{{0, "Shotgun Loadout"}, {1, "Rifle Loadout"}},
				{{0, "Shotgun Loadout"}, {1, "Combat MG Loadout"}}
			},
			{
				{{0, "SMG Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Machine Pistol Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "SMG Loadout"}, {1, "Shotgun Loadout"}}
			},
			{
				{{0, "Micro SMG Loadout"}, {1, "Machine Pistol Loadout"}},
				{{0, "Micro SMG Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Shotgun Loadout"}, {1, "Revolver Loadout"}}},
			{
				{{0, "                                        "}, {1, ""}},
				{{0, ""}, {1, ""}},
				{{0, ""}, {1, ""}}
			}
		};
		static ListCommand _DiamondCasinoHeistWeapon{"diamondcasinoheistweapon", "武器", "Weapon", diamondCasinoHeistWeapon[5][0], 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistGunman = {
			{0, "切斯特.麦考伊"},
			{1, "古斯塔沃.莫塔"},
			{2, "帕特里克.麦克瑞利"},
			{3, "查理.里德"},
			{4, "卡尔.阿卜拉季"},
			{5, "移除枪手"}
		};

		class Gunman : public ListCommand
		{
			using ListCommand::ListCommand;

			virtual void OnChange() override
			{
				_DiamondCasinoHeistWeapon.SetList(diamondCasinoHeistWeapon[this->GetState()][_DiamondCasinoHeistApproachPtr->GetState()]);
				_DiamondCasinoHeistWeapon.SetState(0);
			}
		};
		static Gunman _DiamondCasinoHeistGunman{"diamondcasinoheistgunman", "枪手", "Gunman", diamondCasinoHeistGunman, 5};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistApproach = {
			{0, "隐迹潜踪"},
			{1, "兵不厌诈"},
			{2, "气势汹汹"}
		};

		class Approach : public ListCommand
		{
			using ListCommand::ListCommand;

			virtual void OnChange() override
			{
				_DiamondCasinoHeistWeapon.SetList(diamondCasinoHeistWeapon[_DiamondCasinoHeistGunmanPtr->GetState()][this->GetState()]);
				_DiamondCasinoHeistWeapon.SetState(0);
			}
		};
		static Approach _DiamondCasinoHeistApproach{"diamondcasinoheistapproach", "方式", "Heist approach", diamondCasinoHeistApproach, 0};

		static struct InitPtrs
		{
			InitPtrs()
			{
				_DiamondCasinoHeistGunmanPtr = &_DiamondCasinoHeistGunman;
				_DiamondCasinoHeistApproachPtr = &_DiamondCasinoHeistApproach;
			}
		} _initPtrs;

		static std::vector<std::vector<std::pair<int, const char*>>> diamondCasinoHeistVehicle = {
			{{0, "炸吧"}, {1, "流浪者"}, {2, "不法之徒"}, {3, "埃弗伦"}},
			{{0, "王者经典版"}, {1, "铁腕经典版"}, {2, "爱利"}, {3, "科莫达"}},
			{{0, "随行者MK2"}, {1, "漂移约塞米蒂"}, {2, "斯国一"}, {3, "扼喉"}},
			{{0, "曼切兹"}, {1, "斯特德"}, {2, "亵渎者"}, {3, "雷克卓"}},
			{{0, "Issi Classic"}, {1, "Asbo"}, {2, "Kanjo"}, {3, "Sentinel Classic"}},
			{{0, "                           "}, {1, ""}, {2, ""}, {3, ""}}
		};
		static ListCommand _DiamondCasinoHeistVehicle{"diamondcasinoheistvehicle", "Vehicle", "Vehicle", diamondCasinoHeistVehicle[5], 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistDriver = {
			{0, "切斯特.麦考伊"},
			{1, "陶艾迪"},
			{2, "塔丽娜.马丁内斯"},
			{3, "扎克.尼尔森"},
			{4, "卡里姆.登茨"},
			{5, "移除车手"}
		};

		class Driver : public ListCommand
		{
			using ListCommand::ListCommand;

			virtual void OnChange() override
			{
				_DiamondCasinoHeistVehicle.SetList(diamondCasinoHeistVehicle[this->GetState()]);
				_DiamondCasinoHeistVehicle.SetState(0);
			}
		};
		static Driver _DiamondCasinoHeistDriver{"diamondcasinoheistdriver", "车手", "Driver", diamondCasinoHeistDriver, 5};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistHacker = {
			{4, "阿维.斯瓦兹曼"},
			{5, "佩奇.哈里斯"},
			{2, "克里斯汀.费尔兹"},
			{3, "尤汗.布莱尔"},
			{1, "里奇.卢肯斯"},
			{6, "移除黑客"}
		};
		static ListCommand _DiamondCasinoHeistHacker{"diamondcasinoheisthacker", "黑客", "Hacker", diamondCasinoHeistHacker, 6};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H3_COMPLETEDPOSIX", -1);
				Stats::SetInt("MPX_H3OPT_MASKS", 4);
				Stats::SetInt("MPX_H3OPT_WEAPS", _DiamondCasinoHeistWeapon.GetState());
				Stats::SetInt("MPX_H3OPT_VEHS", _DiamondCasinoHeistVehicle.GetState());
				Stats::SetInt("MPX_CAS_HEIST_FLOW", -1);
				Stats::SetInt("MPX_H3_LAST_APPROACH", 0);
				Stats::SetInt("MPX_H3OPT_APPROACH", _DiamondCasinoHeistApproach.GetState() + 1); // 1 = Silent & Sneaky, 2 = The Big Con, 3 = Aggressive

				switch (_DiamondCasinoHeistDifficulty.GetState())
				{
				case 0: Stats::SetInt("MPX_H3_HARD_APPROACH", 0); break;
				case 1: Stats::SetInt("MPX_H3_HARD_APPROACH", _DiamondCasinoHeistApproach.GetState() + 1); break;
				default: break;
				}

				Stats::SetInt("MPX_H3OPT_TARGET", _DiamondCasinoHeistPrimaryTarget.GetState());
				Stats::SetInt("MPX_H3OPT_POI", 1023);
				Stats::SetInt("MPX_H3OPT_ACCESSPOINTS", 2047);

				switch (_DiamondCasinoHeistGunman.GetState())
				{
				case 0: Stats::SetInt("MPX_H3OPT_CREWWEAP", 4); break;
				case 1: Stats::SetInt("MPX_H3OPT_CREWWEAP", 2); break;
				case 2: Stats::SetInt("MPX_H3OPT_CREWWEAP", 5); break;
				case 3: Stats::SetInt("MPX_H3OPT_CREWWEAP", 3); break;
				case 4: Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); break;
				case 5: Stats::SetInt("MPX_H3OPT_CREWWEAP", 6); break;
				default: break;
				}

				switch (_DiamondCasinoHeistDriver.GetState())
				{
				case 0: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 5); break;
				case 1: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 3); break;
				case 2: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 2); break;
				case 3: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 4); break;
				case 4: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 1); break;
				case 5: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 6); break;
				default: break;
				}

				Stats::SetInt("MPX_H3OPT_CREWHACKER", _DiamondCasinoHeistHacker.GetState());
				Stats::SetInt("MPX_H3OPT_DISRUPTSHIP", 3); // Security Strength: 1 = Strong, 2 = Medium, 3 = Weak
				Stats::SetInt("MPX_H3OPT_BODYARMORLVL", -1);
				Stats::SetInt("MPX_H3OPT_KEYLEVELS", 2); // 1 = Level1 Security Pass, 2 = Level2 Security Pass

				Stats::SetInt("MPX_H3OPT_BITSET0", rand() % (INT_MAX)); // Refresh board
				Stats::SetInt("MPX_H3OPT_BITSET1", rand() % (INT_MAX)); // Refresh board

				ScriptMgr::Yield(500ms);

				Stats::SetInt("MPX_H3OPT_BITSET0", -1); // Refresh board
				Stats::SetInt("MPX_H3OPT_BITSET1", -1); // Refresh board
			}
		};

		static IntCommand _DiamondCasinoHeistPotentialTake{"diamondcasinoheistpotentialtake", "Potential Take", "Updates potential take", std::nullopt, std::nullopt, 0};

		class SetPotentialTake : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int primary_target = Stats::GetInt("MPX_H3OPT_TARGET");

				switch (primary_target)
				{
				case 0:
				{
					static Tunable tunable{static_cast<joaat_t>(-1638885821)};
					if (tunable.IsReady())
						tunable.Set(_DiamondCasinoHeistPotentialTake.GetState());
					break;
				} // "Cash"
				case 1:
				{
					static Tunable tunable{static_cast<joaat_t>(-582734553)};
					if (tunable.IsReady())
						tunable.Set(_DiamondCasinoHeistPotentialTake.GetState());
					break;
				} // "Gold"
				case 2:
				{
					static Tunable tunable{1934398910};
					if (tunable.IsReady())
						tunable.Set(_DiamondCasinoHeistPotentialTake.GetState());
					break;
				} // "Artwork"
				case 3:
				{
					static Tunable tunable{1277889925};
					if (tunable.IsReady())
						tunable.Set(_DiamondCasinoHeistPotentialTake.GetState());
					break;
				} // "Diamond"
				default: break;
				}
			}
		};

		static IntCommand _DiamondCasinoHeistActualTake{"diamondcasinoheistactualtake", "Actual Take", "Updates actual take", std::nullopt, std::nullopt, 0};

		class SetActualTake : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
					*ScriptLocal(thread, 20395).At(2686).As<int*>() = _DiamondCasinoHeistActualTake.GetState();
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
				{
					*ScriptLocal(thread, 54042).As<int*>() = 5;
					*ScriptLocal(thread, 55108).As<int*>() = 5;
				}
			}
		};

		class SkipDrilling : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
					*ScriptLocal(thread, 10551).At(7).As<int*>() = *ScriptLocal(thread, 10551).At(37).As<int*>();
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
				{
					Scripts::ForceScriptHost(thread);
					ScriptMgr::Yield(500ms);

					*ScriptLocal(thread, 20395).At(1740).At(0, 1).As<int*>() = 80;
					*ScriptLocal(thread, 20395).At(2686).As<int*>() = 4443220;
					*ScriptLocal(thread, 20395).At(1062).As<int*>() = 5;
					*ScriptLocal(thread, 20395).As<int*>() = 12;
					*ScriptLocal(thread, 29016).At(0, 1).As<int*>() = 99999;
					*ScriptLocal(thread, 32472).At(0, 294).At(68).As<int*>() = 99999;
				}
			}
		};

		static SetCuts _DiamondCasinoHeistSetCuts{"diamondcasinoheistsetcuts", "设置分红", "设置抢劫分红"};
		static ForceReady _DiamondCasinoHeistForceReady{"diamondcasinoheistforceready", "强制准备", "强制所有玩家准备就绪"};
		static Setup _DiamondCasinoHeistSetup{"diamondcasinoheistsetup", "设置", "设置名钻赌场豪劫"};
		static SetPotentialTake _DiamondCasinoHeistSetPotentialTake{"diamondcasinoheistsetpotentialtake", "Set Potential Take", "Updates potential take"};
		static SetActualTake _DiamondCasinoHeistSetActualTake{"diamondcasinoheistsetactualtake", "Set Actual Take", "Updates actual take"};
		static SkipHacking _DiamondCasinoHeistSkipHacking{"diamondcasinoheistskiphacking", "跳过骇入", "跳过骇入过程"};
		static SkipDrilling _DiamondCasinoHeistSkipDrilling{"diamondcasinoheistskipdrilling", "跳过钻孔", "跳过钻孔过程"};
		static InstantFinish _DiamondCasinoHeistInstantFinish{"diamondcasinoheistinstantfinish", "立刻完成", "立即通过抢劫"};
	}
}