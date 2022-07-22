#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include <cstdint>
#include "..\includes\IniReader.h"
#include <d3d9.h>

DWORD WINAPI Thing(LPVOID);

bool once1 = 0, once2 = 0, once3 = 0;
bool bWindowedMode, CenterWindow, SkipMovies, SkipNISs, IsPlayerNameSet, ExOptsTeamTakeOver, UnlockAllThings, IsOnFocus, EnableSound, EnableMusic, EnableVoice, AutoDrive, DriftMode, ShowMessage, EnableSaveLoadHotPos, UnlockDLC, ShowAllCarsInFE, ShowSpecialVinyls, EnableDebugWorldCamera, DebugCamStatus, DebugWatchCarCamera, GarageZoom, GarageRotate, GarageShowcase, RemoveTopSpeedLimiter;
int ThreadDelay, StartingCash, hotkeyUnlockAllThings, hotkeyAutoDrive, hotkeyPhysSwitch, hotkeyFreezeCamera, hotkeyToggleHeadlights, MaximumLaps, MaximumRepairMarkers;
char* IntroMovieName, * PlayerName;
DWORD GameState;

char* CopyrightString = "© 2007 Electronic Arts Inc. All rights reserved.^NFSPS Extra Options - © 2021 ExOpts Team. No rights reserved.";
DWORD _A7EBC389_New = (DWORD)CopyrightString;
DWORD _44885A91_New;

void(*Game_ForceAIControl)() = (void(*)())0x6EA6F0;
void(*Game_ClearAIControl)() = (void(*)())0x6EA760;
void(*Game_ActivateDriftMode)() = (void(*)())0x6EA9A0;
void(*Game_DeactivateDriftMode)() = (void(*)())0x6EAA00;
void(*Hud_ShowMessage)(char* MessageToShow) = (void(*)(char*))0x6E9630;
void(*CameraAI_SetAction)(int EVIEW_ID, char* Action) = (void(*)(int, char*))0x6494B0;
bool(__thiscall* PVehicle_IsGlareOn)(DWORD* PVehicle, int VehicleFXID) = (bool(__thiscall*)(DWORD*, int))0x727560;
void(__thiscall* PVehicle_GlareOn)(DWORD* PVehicle, int VehicleFXID) = (void(__thiscall*)(DWORD*, int))0x712B30;
void(__thiscall* PVehicle_GlareOff)(DWORD* PVehicle, int VehicleFXID) = (void(__thiscall*)(DWORD*, int))0x712B40;
int(*FE_String_PrintF)(char const* pkg_name, int obj_hash, char const* fmt, ...) = (int(*)(char const*, int, char const*, ...))0x5CE4F0;
int(*FE_String_SetLanguageHash)(char const* pkg_name, int obj_hash, int language) = (int(*)(char const*, int, int))0x5BE5F0;

DWORD StringReplacementCodeCaveExit = 0x595859;

int RetZero()
{
	return 0;
}

void __declspec(naked) StringReplacementCodeCave() // 0x595854
{
	_asm
	{
		mov edx, dword ptr ds : [edi + eax * 0x08]

		cmp edx, 0xA7EBC389 // Player Name
		je ReplaceCopyrightString
		cmp edx, 0x44885A91 // Player Name
		je ReplacePlayerNameString
		jmp originalcode

		ReplaceCopyrightString :
		cmp ExOptsTeamTakeOver, 0x01
			jne originalcode
			cmp once1, 0x01
			je originalcode

			push edx
			mov edx, _A7EBC389_New
			mov dword ptr ds : [edi + eax * 0x08 + 0x04] , edx
			mov once1, 0x01
			pop edx

			jmp originalcode

			ReplacePlayerNameString :
		cmp IsPlayerNameSet, 0x01
			jne originalcode
			cmp once2, 0x01
			je originalcode

			push edx
			mov edx, _44885A91_New
			mov dword ptr ds : [edi + eax * 0x08 + 0x04] , edx
			mov once2, 0x01
			pop edx

			jmp originalcode

			originalcode :
		cmp edx, esi
			jmp StringReplacementCodeCaveExit

	}
}

DWORD RepairMarkerCodeCave_HighlightNextSetting_Exit = 0x7DE652;

void __declspec(naked) RepairMarkerCodeCave_HighlightNextSetting()
{
	_asm
	{
		mov edx, MaximumRepairMarkers
		mov dword ptr ds : [ecx + eax * 8 + 0x14] , edx
		push edi
		jmp RepairMarkerCodeCave_HighlightNextSetting_Exit
	}
}

DWORD RepairMarkerStringCodeCave_HighlightPrevSetting_Exit = 0x7de82e;

void __declspec(naked) RepairMarkerStringCodeCave_HighlightPrevSetting()
{
	_asm
	{
		cmp eax, 0x33F5A29A // SCROLL_DATA_4
		jne originalcode

		mov edx, [esp + 0x10] // marker count
		push edx
		push 0x96FDC0 // "{0:d}"
		push eax // obj_hash
		push ebx // pkg_name
		call FE_String_PrintF
		add esp, 8
		jmp RepairMarkerStringCodeCave_HighlightPrevSetting_Exit

		originalcode :
		push eax
			push ebx
			call FE_String_SetLanguageHash

			jmp RepairMarkerStringCodeCave_HighlightPrevSetting_Exit
	}
}


DWORD RepairMarkerStringCodeCave_HighlightNextSetting_Exit = 0x7DE6F7;

void __declspec(naked) RepairMarkerStringCodeCave_HighlightNextSetting()
{
	_asm
	{
		cmp eax, 0x33F5A29A // SCROLL_DATA_4
		jne originalcode

		mov edx, [esp + 0x10] // marker count
		push edx
		push 0x96FDC0 // "{0:d}"
		push eax // obj_hash
		push ebx // pkg_name
		call FE_String_PrintF
		add esp, 8
		jmp RepairMarkerStringCodeCave_HighlightNextSetting_Exit

		originalcode :
		push eax
			push ebx
			call FE_String_SetLanguageHash

			jmp RepairMarkerStringCodeCave_HighlightNextSetting_Exit
	}
}


DWORD RepairMarkerStringCodeCave_DisplayRaceDaySettings_Exit = 0x7DE214;

void __declspec(naked) RepairMarkerStringCodeCave_DisplayRaceDaySettings()
{
	_asm
	{
		cmp eax, 0x33F5A29A // SCROLL_DATA_4
		jne originalcode

		mov edx, [esp + 0x18] // marker count
		push edx
		push 0x96FDC0 // "{0:d}"
		push eax // obj_hash
		push esi // pkg_name
		call FE_String_PrintF
		add esp, 8
		jmp RepairMarkerStringCodeCave_DisplayRaceDaySettings_Exit

		originalcode :
		push eax
			push esi
			call FE_String_SetLanguageHash

			jmp RepairMarkerStringCodeCave_DisplayRaceDaySettings_Exit
	}
}

void Init()
{
	// Read values from .ini
	CIniReader iniReader("NFSPSExtraOptionsSettings.ini");

	// Hotkeys
	hotkeyToggleHeadlights = iniReader.ReadInteger("Hotkeys", "Headlights", 72); // H
	hotkeyFreezeCamera = iniReader.ReadInteger("Hotkeys", "FreezeCamera", 19); // Pause/Break
	hotkeyUnlockAllThings = iniReader.ReadInteger("Hotkeys", "UnlockAllThings", 116); // F5
	hotkeyAutoDrive = iniReader.ReadInteger("Hotkeys", "AutoDrive", 117); // F6
	hotkeyPhysSwitch = iniReader.ReadInteger("Hotkeys", "PhysSwitch", 75); // K
	EnableSaveLoadHotPos = iniReader.ReadInteger("Hotkeys", "EnableSaveLoadHotPos", 0) == 1;

	// Lap Controllers
	MaximumLaps = iniReader.ReadInteger("LapControllers", "Maximum", 5);
	MaximumRepairMarkers = iniReader.ReadInteger("LapControllers", "MaximumRepairMarkers", 5);

	// Menu
	ShowSpecialVinyls = iniReader.ReadInteger("Menu", "ShowSpecialVinyls", 1) == 1;
	IntroMovieName = iniReader.ReadString("Menu", "IntroMovie", "FE_BG");
	GarageZoom = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteZoom", 0) == 1;
	GarageRotate = iniReader.ReadInteger("Menu", "ShowcaseCamInfiniteRotation", 0) == 1;
	GarageShowcase = iniReader.ReadInteger("Menu", "ShowcaseCamAlwaysEnable", 0) == 1;
	ExOptsTeamTakeOver = iniReader.ReadInteger("Menu", "DisableTakeover", 0) == 0;

	// Gameplay
	EnableDebugWorldCamera = iniReader.ReadInteger("Gameplay", "EnableDebugCamera", 0) == 1;
	PlayerName = iniReader.ReadString("Gameplay", "PlayerName", "0");
	StartingCash = iniReader.ReadInteger("Gameplay", "StartingCash", 10000);
	RemoveTopSpeedLimiter = iniReader.ReadInteger("Gameplay", "RemoveTopSpeedLimiter", 1) == 1;
	UnlockAllThings = iniReader.ReadInteger("Gameplay", "UnlockAllThings", 0) == 1;
	UnlockDLC = iniReader.ReadInteger("Gameplay", "UnlockDLC", 1) == 1;
	ShowAllCarsInFE = iniReader.ReadInteger("Gameplay", "ShowAllCarsInFE", 0) == 1;

	// Misc
	SkipMovies = iniReader.ReadInteger("Misc", "SkipMovies", 0) == 1;
	SkipNISs = iniReader.ReadInteger("Misc", "SkipNISs", 0) == 1;
	EnableSound = iniReader.ReadInteger("Misc", "EnableSound", 1) == 1;
	EnableMusic = iniReader.ReadInteger("Misc", "EnableMusic", 1) == 1;
	EnableVoice = iniReader.ReadInteger("Misc", "EnableVoice", 1) == 1;
	ShowMessage = iniReader.ReadInteger("Misc", "ShowMessage", 1) == 1;
	//AllowMultipleInstances = iniReader.ReadInteger("Misc", "AllowMultipleInstances", 0) == 1;
	ThreadDelay = iniReader.ReadInteger("Misc", "ThreadDelay", 5);
	CenterWindow = iniReader.ReadInteger("Misc", "CenterWindow", 1) == 1;

	// Restrictions (wrap values around)
	MaximumLaps %= 128;
	MaximumRepairMarkers %= 128;

	// Set maximum lap count
	injector::MakeRangedNOP(0x7F8FF0, 0x7F8FF6, true);
	injector::WriteMemory<BYTE>(0x7F8FF0, 0xB8, true); // mov eax,
	injector::WriteMemory<int>(0x7F8FF1, MaximumLaps - 1, true); // MaximumLaps

	// Set maximum repair marker count
	injector::WriteMemory<BYTE>(0x56FDD6, MaximumRepairMarkers + 1, true); // DALRaceDayCommands::GetRaceDaySlotOptionsForIndex::Execute
	// injector::MakeJMP(0x7DE64D, RepairMarkerCodeCave_HighlightNextSetting, true);
	// injector::MakeRangedNOP(0x7DE658, 0x7DE65B, true); // FERaceDayManageScreen::HighlightNextSetting
	injector::MakeJMP(0x7de827, RepairMarkerStringCodeCave_HighlightPrevSetting, true);
	injector::MakeJMP(0x7DE6F0, RepairMarkerStringCodeCave_HighlightNextSetting, true);
	injector::MakeJMP(0x7DE20D, RepairMarkerStringCodeCave_DisplayRaceDaySettings, true);

	// Set Intro Movie Name
	injector::WriteMemory(0x7E2CEB, IntroMovieName, true);

	// Takeover
	// Force Name
	if (strcmp(PlayerName, "0") != 0)
	{
		IsPlayerNameSet = 1;
		_44885A91_New = (DWORD)PlayerName;
	}

	injector::MakeJMP(0x595854, StringReplacementCodeCave, true);

	// Starting Cash
	injector::WriteMemory<int>(0xA9DA1C, StartingCash, true);

	// Add Special vinyls to shop
	if (ShowSpecialVinyls)
	{
		injector::WriteMemory<BYTE>(0x7e9dce, 0x1B, true);
		injector::WriteMemory<BYTE>(0x7E9DD7, 0x1C, true);

		// Make all vinyls colorable
		injector::MakeNOP(0x7CE600, 2, true);
		injector::MakeNOP(0x7CE607, 2, true);
		injector::MakeNOP(0x7CE60E, 2, true);
		injector::MakeNOP(0x7CE615, 2, true);

		// Make all vinyls Transformable
		injector::MakeNOP(0x7CE581, 2, true);
		injector::MakeNOP(0x7CE588, 2, true);

		// Make all vinyls editable
		injector::MakeNOP(0x7CE653, 2, true);
		injector::MakeNOP(0x7CE65A, 2, true);
		injector::MakeNOP(0x7CE661, 2, true);
		injector::MakeNOP(0x7CE668, 2, true);
		injector::WriteMemory<BYTE>(0x7CE678, 0xEB, true);

		// Remove Vinyl - Car Specifications 
		injector::MakeNOP(0x7E9DB5, 6, true);
		injector::MakeNOP(0x7E9DC6, 6, true);
	}

	// Garage Camera Hacks
	if (GarageZoom)
	{
		injector::WriteMemory<BYTE>(0x652511, 0xEB, true); // FOV
	}
	if (GarageRotate)
	{
		injector::WriteMemory<BYTE>(0x652486, 0xEB, true);
	}
	if (GarageShowcase)
	{
		injector::MakeNOP(0x7CB8B3, 6, true); // + zoom with mouse wheel
	}

	// Unlock All Things - Load preference
	if (UnlockAllThings)
	{
		injector::WriteMemory<unsigned char>(0xBFBC5B, 1, true);
	}

	// Unlock DLC - thanks to SAAM007
	if (UnlockDLC)
	{
		char* saambp1 = "saam-bp1";
		char* saambp2 = "saam-bp2";
		char* saamunl = "saam-unl";
		char* saamce = "saam-ce";

		for (int i = 0; i < 8; i++)
		{
			injector::WriteMemory<char>(0x99E034 + i, saambp1[i], true);
			injector::WriteMemory<char>(0xA51AF8 + i, saambp1[i], true);
			injector::WriteMemory<char>(0x99E040 + i, saambp2[i], true);
			injector::WriteMemory<char>(0xA51AC4 + i, saambp2[i], true);
			injector::WriteMemory<char>(0x99E04C + i, saamunl[i], true);
			injector::WriteMemory<char>(0xA51A90 + i, saamunl[i], true);
			if (i < 7)
			{
				injector::WriteMemory<char>(0x99E058 + i, saamce[i], true);
				injector::WriteMemory<char>(0xA51A5C + i, saamce[i], true);
			}
		}

		injector::WriteMemory<BYTE>(0xA51A80, 0x11, true);
		injector::WriteMemory<BYTE>(0xA51A8C, 0x01, true);
		injector::WriteMemory<BYTE>(0xA51AB4, 0x00, true);
		injector::WriteMemory<BYTE>(0xA51AE8, 0x13, true);
		injector::WriteMemory<BYTE>(0xA51AF4, 0x01, true);
		injector::WriteMemory<BYTE>(0xA51B1C, 0x12, true);
		injector::WriteMemory<BYTE>(0xA51AF4, 0x01, true);
	}

	// Show All Cars In FE
	if (ShowAllCarsInFE)
	{
		injector::WriteMemory<unsigned char>(0xBFBC6E, 1, true);
	}

	if (SkipMovies)
	{
		injector::WriteMemory<unsigned char>(0xBFBC74, SkipMovies, true);
	}

	if (SkipNISs)
	{
		injector::WriteMemory<unsigned char>(0xBFBC28, SkipNISs, true);
	}

	if (!EnableSound)
	{
		injector::WriteMemory<unsigned char>(0xA9DA00, EnableSound, true);
	}

	if (!EnableMusic)
	{
		injector::WriteMemory<unsigned char>(0xA9DA04, EnableMusic, true);
	}

	if (!EnableVoice)
	{
		injector::WriteMemory<unsigned char>(0xA9DA08, EnableVoice, true);
	}
	if (ShowMessage)
	{
		injector::WriteMemory<DWORD>(0x6E96C2, 0xA2B7D07C, true); // Fix messages not appearing
	}

	// Remove Top Speed Limiter
	if (RemoveTopSpeedLimiter)
	{
		injector::WriteMemory<unsigned int>(0x0040BE15, 0, true);
		injector::WriteMemory<unsigned int>(0x004887A3, 0, true);
		injector::WriteMemory<unsigned int>(0x00488AA9, 0, true);
		injector::WriteMemory<unsigned int>(0x00488AE3, 0, true);
		injector::WriteMemory<unsigned int>(0x00718B3F, 0, true);
		injector::WriteMemory<unsigned int>(0x0071E4E8, 0, true);
		injector::MakeJMP(0x00402820, RetZero, true);
	}

	// Other things
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Thing, NULL, 0, NULL);
}

DWORD WINAPI Thing(LPVOID)
{
	while (true)
	{
		Sleep(ThreadDelay);

		GameState = *(DWORD*)0xABB510; // 3 = FE, 4&5 = Loading screen, 6 = Gameplay
		IsOnFocus = !(*(bool*)0xAC1055);

		if ((GetAsyncKeyState(hotkeyUnlockAllThings) & 1) && IsOnFocus) // Unlock All Things
		{
			CIniReader iniReader("NFSPSExtraOptionsSettings.ini");
			UnlockAllThings = !UnlockAllThings;
			iniReader.WriteInteger("Gameplay", "UnlockAllThings", UnlockAllThings);

			if (UnlockAllThings)
			{
				injector::WriteMemory<unsigned char>(0xBFBC5B, 1, true);
			}

			else
			{
				injector::WriteMemory<unsigned char>(0xBFBC5B, 0, true);
			}

			while ((GetAsyncKeyState(hotkeyUnlockAllThings) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// AutoDrive
		if ((GetAsyncKeyState(hotkeyAutoDrive) & 1) && (GameState == 6) && IsOnFocus)
		{
			AutoDrive = !AutoDrive;

			if (AutoDrive)
			{
				Game_ForceAIControl();
			}
			else
			{
				Game_ClearAIControl();
			}

			while ((GetAsyncKeyState(hotkeyAutoDrive) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Drift Mode
		if ((GetAsyncKeyState(hotkeyPhysSwitch) & 1) && (GameState == 6) && IsOnFocus) //When pressed "Phys Switch"
		{
			DriftMode = !DriftMode; // Toggle option

			if (DriftMode)
			{
				Game_ActivateDriftMode();
				if (ShowMessage) Hud_ShowMessage("^Drift physics are enabled.");
			}
			else
			{
				Game_DeactivateDriftMode();
				if (ShowMessage) Hud_ShowMessage("^Drift physics are disabled.");
			}

			while ((GetAsyncKeyState(hotkeyPhysSwitch) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Headlights (Doesn't work in NFSPS)
		if ((GetAsyncKeyState(hotkeyToggleHeadlights) & 1) && (GameState == 6) && IsOnFocus) // When pressed "Toggle Head Lights" key
		{
			DWORD* PlayerPVehicle = *(DWORD**)0xACE110;

			if (PlayerPVehicle)
			{
				if (!PVehicle_IsGlareOn(PlayerPVehicle, 7)) // Enable headlights
				{
					injector::WriteMemory<unsigned char>(0x717C5D, 7, true);
					PVehicle_GlareOn(PlayerPVehicle, 7);
				}

				else // Disable headlights
				{
					injector::WriteMemory<unsigned char>(0x717C5D, 0, true);
					PVehicle_GlareOff(PlayerPVehicle, 7);
				}
			}

			while ((GetAsyncKeyState(hotkeyToggleHeadlights) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Freeze Camera
		if ((GetAsyncKeyState(hotkeyFreezeCamera) & 1) && IsOnFocus)
		{
			*(bool*)0xAB4960 = !(*(bool*)0xAB4960);

			while ((GetAsyncKeyState(hotkeyFreezeCamera) & 0x8000) > 0) { Sleep(ThreadDelay); }
		}

		// Debug Camera
		if (EnableDebugWorldCamera && (GameState == 6) && IsOnFocus)
		{
			if ((GetAsyncKeyState(VK_BACK) & 1))
			{
				DebugCamStatus = !DebugCamStatus;
				if (DebugCamStatus) CameraAI_SetAction(1, "CDActionDebug");
				else CameraAI_SetAction(1, "CDActionDrive");

				while ((GetAsyncKeyState(VK_BACK) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}

			if ((GetAsyncKeyState(VK_NEXT) & 1)) // Page Down : Toggle Debug Watch Car Camera
			{
				DebugWatchCarCamera = !DebugWatchCarCamera;
				*(unsigned char*)0xAB499C = 1;

				if (DebugWatchCarCamera)
				{
					*(unsigned char*)0xAB4961 = 1;
					CameraAI_SetAction(1, "CDActionDebugWatchCar");
				}

				else
				{
					CameraAI_SetAction(1, "CDActionDrive");
					*(unsigned char*)0xAB4961 = 0;
				}

				while ((GetAsyncKeyState(VK_NEXT) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}

			if ((GetAsyncKeyState(VK_ADD) & 1) && DebugWatchCarCamera) // + : Next car
			{
				*(unsigned char*)0xAB499C += 1;

				while ((GetAsyncKeyState(VK_ADD) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}

			if ((GetAsyncKeyState(VK_SUBTRACT) & 1) && DebugWatchCarCamera) // - : Previous car
			{
				*(unsigned char*)0xAB499C -= 1;

				while ((GetAsyncKeyState(VK_SUBTRACT) & 0x8000) > 0) { Sleep(ThreadDelay); }
			}
		}

		// .hot Save And Load
		if (EnableSaveLoadHotPos && (GameState == 6) && IsOnFocus)
		{
			// Save
			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(49) & 0x8000)
			{
				*(unsigned int*)0xAEB6A8 = 1;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 1.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(50) & 0x8000)
			{
				*(unsigned int*)0xAEB6A8 = 2;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 2.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(51) & 0x8000)
			{
				*(unsigned int*)0xAEB6A8 = 3;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 3.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(52) & 0x8000)
			{
				*(unsigned int*)0xAEB6A8 = 4;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 4.");
			}

			if (GetAsyncKeyState(VK_LSHIFT) & GetAsyncKeyState(53) & 0x8000)
			{
				*(unsigned int*)0xAEB6A8 = 5;
				if (ShowMessage) Hud_ShowMessage("^Saved position data to slot 5.");
			}


			// Load
			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(49) & 0x8000)
			{
				*(unsigned int*)0xAEB6AC = 1;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 1.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(50) & 0x8000)
			{
				*(unsigned int*)0xAEB6AC = 2;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 2.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(51) & 0x8000)
			{
				*(unsigned int*)0xAEB6AC = 3;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 3.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(52) & 0x8000)
			{
				*(unsigned int*)0xAEB6AC = 4;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 4.");
			}

			if (GetAsyncKeyState(VK_LCONTROL) & GetAsyncKeyState(53) & 0x8000)
			{
				*(unsigned int*)0xAEB6AC = 5;
				if (ShowMessage) Hud_ShowMessage("^Loaded position data from slot 5.");
			}
		}
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);

		if (strstr((const char*)(base + (0xA49742 - base)), "ProStreet08Release.exe"))
			Init();

		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use a NOCD v1.1 NFS.exe.", "NFSPS Extra Options", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;

}

