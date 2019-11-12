#include <stdio.h>
#include <time.h>
#include <windows.h>

int random() {
    srand(time(NULL));
    return rand();
}

void handleHWND(HWND hwnd) {
    if(NULL == hwnd) { return; }
    if(GetForegroundWindow() == hwnd) {
        printf("Active Window... Ignore\n");
        return;
    }

    int keys[] = {VK_SPACE, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN};
    int action = keys[random() % (sizeof(keys)/sizeof(*keys)) ];

    printf("Send Action: %d\n", action);
    SendMessage(hwnd, WM_KEYDOWN, action, 0);
    Sleep(random() % 500);
    SendMessage(hwnd, WM_KEYUP, action, 0 );
}

BOOL CALLBACK EnumWindowsProc(
  _In_ HWND   hwnd,
  _In_ LPARAM lParam
) {
    char name[1000] = {0}, className[1000] = {0};
    if(GetWindowText(hwnd, name, sizeof(name)) > 0, GetClassName(hwnd, className, sizeof(className)) > 0) {
        if(strcmp(className, "GxWindowClass") == 0) //WOW
        {
            printf("Handle = %p ", hwnd);
            printf("Title = '%s' ", name);
            printf("Class = '%s' ", className);
            printf("\n");

            handleHWND(hwnd);
        }
    }
    return TRUE;
}

int main(int argc, char** argv) {
    for(;;) {
        if(!EnumWindows(EnumWindowsProc, 0)) {
            printf("Enum Windows Failed\n");
        }
        Sleep(1000 * (random() % 10) );
    }
    return 0;
}