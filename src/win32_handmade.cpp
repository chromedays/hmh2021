#include <Windows.h>

LRESULT CALLBACK MainWindowCallback(HWND Window, UINT Message, WPARAM WParam,
                                    LPARAM LParam) {
  LRESULT Result = 0;

  switch (Message) {
  case WM_SIZE: {
    OutputDebugStringA("WM_SIZE\n");
  } break;

  case WM_DESTROY: {
    OutputDebugStringA("WM_DESTROY\n");
  } break;

  case WM_CLOSE: {
    OutputDebugStringA("WM_CLOSE\n");
  } break;

  case WM_ACTIVATEAPP: {
    OutputDebugStringA("WM_ACTIVATEAPP\n");
  } break;

  case WM_PAINT: {
    PAINTSTRUCT Paint;
    HDC DeviceContext = BeginPaint(Window, &Paint);
    int X = Paint.rcPaint.left;
    int Y = Paint.rcPaint.top;
    int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
    int Width = Paint.rcPaint.right - Paint.rcPaint.left;
    static DWORD Operation = WHITENESS;
    if (Operation == WHITENESS) {
      Operation = BLACKNESS;
    } else {
      Operation = WHITENESS;
    }
    PatBlt(DeviceContext, X, Y, Width, Height, Operation);
    EndPaint(Window, &Paint);
  } break;

  default: {
    Result = DefWindowProcA(Window, Message, WParam, LParam);
  } break;
  }

  return Result;
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance,
                     LPSTR CommandLine, int ShowCode) {
  WNDCLASS WindowClass = {};

  // TODO(casey): Check if HREDRAW/VREDRAW/OWNDC still matter
  WindowClass.lpfnWndProc = MainWindowCallback;
  WindowClass.hInstance = Instance;
  // WindowClass.hIcon
  WindowClass.lpszClassName = "HandmadeHeroWindowClass";

  if (RegisterClassA(&WindowClass)) {
    HWND WindowHandle = CreateWindowExA(
        0, WindowClass.lpszClassName, "Handmade Hero",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, Instance, 0);
    if (WindowHandle) {
      MSG Message;
      for (;;) {
        BOOL MessageResult = GetMessageA(&Message, 0, 0, 0);
        if (MessageResult > 0) {
          TranslateMessage(&Message);
          DispatchMessageA(&Message);
        } else {
          break;
        }
      }
    } else {
      // TODO(casey): Logging
    }
  } else {
    // TODO(casey): Logging
  }

  return 0;
}