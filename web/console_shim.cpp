#include "console_shim.h"
#include <iostream>
#include <streambuf>
#include <cstring>

#define EXPORT(name) extern "C" __attribute__((export_name(name)))
#define IMPORT(name) __attribute__((import_module("env"), import_name(name)))

IMPORT("play_sound") void js_play_sound(const char* name, int loop);

static unsigned char g_chars[WEB_ROWS][WEB_COLS];
static unsigned char g_colors[WEB_ROWS][WEB_COLS];
static int g_x = 0, g_y = 0, g_color = 15;

// std::cout is redirected here: every character lands in the grid at the cursor
struct GridBuf : std::streambuf {
    int overflow(int c) override {
        if (c == EOF) return 0;
        if (c == '\n') { g_x = 0; g_y++; return c; }
        if (g_x >= 0 && g_x < WEB_COLS && g_y >= 0 && g_y < WEB_ROWS) {
            g_chars[g_y][g_x] = (unsigned char)c;
            g_colors[g_y][g_x] = (unsigned char)g_color;
        }
        g_x++;
        return c;
    }
};
static GridBuf g_buf;

void web_console_init() {
    std::memset(g_chars, ' ', sizeof g_chars);
    std::memset(g_colors, 0, sizeof g_colors);
    g_x = g_y = 0; g_color = 15;
    std::cout.rdbuf(&g_buf);
}

HANDLE GetStdHandle(DWORD) { return (HANDLE)1; }
BOOL SetConsoleCursorInfo(HANDLE, const CONSOLE_CURSOR_INFO*) { return TRUE; }
BOOL SetConsoleCursorPosition(HANDLE, COORD c) { g_x = c.X; g_y = c.Y; return TRUE; }
BOOL SetConsoleTextAttribute(HANDLE, int color) { g_color = color & 15; return TRUE; }

BOOL PlaySoundA(const char* sound, void*, DWORD flags) {
    js_play_sound(sound, (flags & SND_LOOP) ? 1 : 0);
    return TRUE;
}

EXPORT("web_chars")  unsigned char* web_chars()  { return &g_chars[0][0]; }
EXPORT("web_colors") unsigned char* web_colors() { return &g_colors[0][0]; }
EXPORT("web_cols")   int web_cols() { return WEB_COLS; }
EXPORT("web_rows")   int web_rows() { return WEB_ROWS; }
