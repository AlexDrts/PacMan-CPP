#pragma once
// Minimal emulation of the WinAPI console functions the game uses,
// so the same C++ code can be compiled to WebAssembly and run in a browser.
// Output goes into a character grid that the web page draws on a <canvas>.

typedef void* HANDLE;
typedef short SHORT;
typedef unsigned long DWORD;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define WINAPI
#define STD_OUTPUT_HANDLE ((DWORD)-11)

struct COORD { SHORT X; SHORT Y; };
struct CONSOLE_CURSOR_INFO { DWORD dwSize; BOOL bVisible; };

HANDLE GetStdHandle(DWORD);
BOOL SetConsoleCursorPosition(HANDLE, COORD);
BOOL SetConsoleTextAttribute(HANDLE, int);
BOOL SetConsoleCursorInfo(HANDLE, const CONSOLE_CURSOR_INFO*);

#define SND_SYNC     0x0000
#define SND_ASYNC    0x0001
#define SND_LOOP     0x0008
#define SND_FILENAME 0x20000
BOOL PlaySoundA(const char* sound, void* module, DWORD flags);

// Grid size: map (36x19) + coin counter on the right + messages below
#define WEB_COLS 50
#define WEB_ROWS 22

void web_console_init();
