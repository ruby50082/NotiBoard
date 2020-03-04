#include "stdafx.h"
#include "LogitechLEDLib.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "stdafx.h"
#include <iostream>

using namespace std;
void keyboard(unsigned char key)
{
	switch (key)
	{
	case 'f': case 'F':
		ShellExecute(NULL, "open", "www.facebook.com/messages", NULL, NULL, SW_SHOWNORMAL);
		break;
	case 'm': case 'M':
		system("start D:/Downloads/mail.lnk");
		break;
	case 's': case 'S':
		system("start D:/Downloads/Skype.lnk");
		break;
	case 'l': case 'L':
		system("start D:/Downloads/Line.lnk");
		break;
	case 'w': case 'W':
		system("start D:/Downloads/wfeather.lnk");
		break;
	case 'g': case 'G':
		system("start D:/Downloads/GHUB.lnk");
		break;
	case 'y': case 'Y':
		ShellExecute(NULL, "open", "www.youtube.com", NULL, NULL, SW_SHOWNORMAL);
		break;
	case 'i': case 'I':
		keybd_event(VK_LWIN, 0, 0, 0);
		keybd_event(65, 0, 0, 0);
		keybd_event(65, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
		break;
	default:
		break;
	}

}

bool isDesktopAvailable()
{
	HDESK desktop = OpenDesktop(TEXT("Default"), 0, false, DESKTOP_SWITCHDESKTOP);
	if (desktop)
	{
		if (SwitchDesktop(desktop))
		{
			CloseDesktop(desktop);
			return true;
		}
		else
		{
			CloseDesktop(desktop);
		}
	}

	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	bool flag = false;

	while (1) 
	{
		char notiInfoFile[] = "C:\\Users\\User\\Downloads\\933a2a01-b3c8-4292-9d6e-455e88a81139_4sdaedqydyjdm!App\\notifications.txt";
		char notiCnt[1000];
		if (!isDesktopAvailable()) {

			// Initialize the LED SDK
			if (!flag)
			{
				bool LedInitialized = LogiLedInitWithName("SetTargetZone Sample C++");
				flag = true;

				if (!LedInitialized)
				{
					std::cout << "LogiLedInit() failed." << std::endl;
					return 0;
				}
			}

			// Read Notifications
			int msgType;

			memset(notiCnt, 0, sizeof(notiCnt));
			FILE * pFile = fopen(notiInfoFile, "r");
			while (fscanf(pFile, "%d", &msgType) != EOF)
				notiCnt[msgType]++;
			fclose(pFile);
			remove(notiInfoFile);
			Sleep(500);

			LogiLedSetTargetDevice(LOGI_DEVICETYPE_ALL);

			// Set all devices to Black
			LogiLedSetLighting(0, 0, 0);

			// Set some keys on keyboard 
			
			if ( notiCnt[1] == 0 )
				LogiLedPulseSingleKey(LogiLed::KeyName::F, 80, 80, 0, 7, 87, 70, 1000, 1);
			else
				LogiLedFlashSingleKey(LogiLed::KeyName::F, 86, 42, 5, INT_MAX, 5);


			if (notiCnt[2] == 0)
				LogiLedPulseSingleKey(LogiLed::KeyName::L, 80, 80, 0, 7, 87, 70, 1000, 1);
			else
				LogiLedFlashSingleKey(LogiLed::KeyName::L, 21, 21, 80, INT_MAX, 5);

			if (notiCnt[3] == 0)
				LogiLedPulseSingleKey(LogiLed::KeyName::S, 80, 80, 0, 7, 87, 70, 1000, 1);
			else
				LogiLedFlashSingleKey(LogiLed::KeyName::S, 80, 0, 0, INT_MAX, 5);

			if (notiCnt[4] == 0)
				LogiLedPulseSingleKey(LogiLed::KeyName::G, 80, 80, 0, 7, 87, 70, 1000, 1);
			else
				LogiLedFlashSingleKey(LogiLed::KeyName::G, 100, 82, 8, INT_MAX, 5);


			LogiLedPulseSingleKey(LogiLed::KeyName::W, 80, 80, 0, 7, 87, 70, 1000, 1);

			LogiLedPulseSingleKey(LogiLed::KeyName::Y, 80, 80, 0, 7, 87, 70, 1000, 1);
			LogiLedPulseSingleKey(LogiLed::KeyName::M, 80, 80, 0, 7, 87, 70, 1000, 1);
			LogiLedPulseSingleKey(LogiLed::KeyName::I, 80, 80, 0, 7, 87, 70, 1000, 1);

			// have notifications
			/*LogiLedFlashSingleKey(LogiLed::KeyName::W, 60, 0, 80, INT_MAX, 5);

			LogiLedFlashSingleKey(LogiLed::KeyName::Y, 80, 80, 0, INT_MAX, 5);
			LogiLedFlashSingleKey(LogiLed::KeyName::M, 40, 60, 0, INT_MAX, 5);
			LogiLedFlashSingleKey(LogiLed::KeyName::I, 0, 40, 60, INT_MAX, 5);
			*/
			char key = _getch();
			keyboard(key);

			LogiLedShutdown();
			flag = false;

		}

		
		continue;
	}

}