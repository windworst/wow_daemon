#include <stdio.h>
#include <time.h>
#include <windows.h>

int random() {
    srand(time(NULL));
    return rand();
}

void typeString(HWND hwnd, const char* str) {
  for(int i = 0, c = 0; (c = str[i]) != '\0'; ++i) {
    SendMessage(hwnd, WM_CHAR, c, 0);
    Sleep(random() % 100);
  }
}

BOOL CALLBACK EnumWindowsProc(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
    char name[1000] = {0}, className[1000] = {0};
    if(hwnd != NULL && (GetWindowText(hwnd, name, sizeof(name)) > 0, GetClassName(hwnd, className, sizeof(className)) > 0) ) {
        if(strcmp(className, "GxWindowClass") == 0) //WOW
        {
            printf("Handle = %p ", hwnd);
            printf("Title = '%s' ", name);
            printf("Class = '%s' ", className);
            printf("\n");

            if(GetForegroundWindow() == hwnd) {
                printf("Active Window... Ignore\n");
                return TRUE;
            }

            printf("Send Keys\n");

            SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
            Sleep(random() % 100);
            SendMessage(hwnd, WM_KEYUP, VK_RETURN, 0 );
            Sleep(random() % 100);
            if (lParam == 0) {
              typeString(hwnd, "/camp");
            } else {
              typeString(hwnd, "/dance");
            }
            SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
            Sleep(random() % 100);
            SendMessage(hwnd, WM_KEYUP, VK_RETURN, 0 );
        }
    }
    return TRUE;
}

int main(int argc, char** argv) {
    for(int i = 1, n = 80;; ++i) {
        if(!EnumWindows(EnumWindowsProc, i % n)) {
            printf("Enum Windows Failed\n");
        }
        Sleep(1000 * (random() % 10) );
    }
    return 0;
}