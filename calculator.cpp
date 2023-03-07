#include <windows.h>
#include <cstdio>
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	static HWND hwndInput1, hwndInput2, hwndText;
	static HWND hwndButtonAdd, hwndButtonSub, hwndButtonMul, hwndButtonDiv;
	switch(Message) {
		case WM_CREATE: {
			
			hwndInput1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_LEFT , 45, 40, 150, 25, hwnd, (HMENU)1, NULL, NULL);
            hwndInput2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_LEFT , 45, 70, 150, 25, hwnd, (HMENU)2, NULL, NULL);
            HWND hwndText = CreateWindowEx(0, "STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE, 30, 10, 180, 25, hwnd, NULL, NULL, NULL);

			hwndButtonAdd = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 60, 110, 25, 25, hwnd, (HMENU)4, NULL, NULL);
			hwndButtonSub = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 90, 110, 25, 25, hwnd, (HMENU)5, NULL, NULL);
			hwndButtonMul = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 120, 110, 25, 25, hwnd, (HMENU)6, NULL, NULL);
			hwndButtonDiv = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 150, 110, 25, 25, hwnd, (HMENU)7, NULL, NULL);
			break;
		}
		case WM_COMMAND: {
			if (LOWORD(wParam) >= 4 && LOWORD(wParam) <= 7) {
				char input1[256], input2[256], result[256];
				GetWindowText(hwndInput1, input1, 256);
				GetWindowText(hwndInput2, input2, 256);
				double num1 = atof(input1);
				double num2 = atof(input2);
				double res = 0;
				switch (LOWORD(wParam)) {
					case 4: res = num1 + num2; break;
					case 5: res = num1 - num2; break;
					case 6: res = num1 * num2; break;
					case 7: res = num1 / num2; break;
				}
				sprintf(result, "%f", res);
				MessageBox(hwnd, result, "Result", MB_OK);
			}
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);


	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
