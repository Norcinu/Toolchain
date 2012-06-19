#ifndef APP_UTILITIES_H
#define APP_UTILITIES_H

#define VC_EXTRALEAN

#include <Windows.h>
#include <tchar.h>
#include <string>

namespace app_helper
{
	typedef std::basic_string<TCHAR> ustring;

    //RECT& (*UpdateRectangle)(RECT& rec, int amount) = nullptr; 
    
    RECT& AddRectTop(RECT& r, int amount) 
    {
        r.top += amount;
        return r;
    }
    
    RECT& SubtractRectTop(RECT& r, int amount) 
    { 
        r.top -= amount;
        return r; 
    }

    RECT& AddRectLeft(RECT& r, int amount) 
    {
        r.left += amount; 
        return r;
    }
    
    RECT& SubtractRectLeft(RECT& r, int amount) 
    {
        r.left -= amount;
        return r;
    }
        
    /*RECT UpdateRect(RECT r, int amount, RECT& (*UpdateRectangle)(RECT&, int))
    {
    RECT updated = (*UpdateRectangle)(r, amount);
    return std::move(updated);
    }*/
    // this is fucking ugly. add a function pointer to decide addition or subtraction?
    void UpdateRect(RECT * r, int bottom = 0, int left = 0, int right = 0, int top = 0)
    {
        r->bottom += bottom; r->left += left; r->right += right; r->top += top;
    }

	int PrintErrorMessage(const ustring& message)
	{
		return MessageBox(0, message.c_str(), "Error Message", MB_OK|MB_ICONEXCLAMATION);
	}

	UINT AddString(const HWND listbox, const ustring& message)
	{
		return static_cast<UINT>(SendMessage(listbox, LB_ADDSTRING, 0, 
            reinterpret_cast<LPARAM>(message.c_str())));
	}

	HWND CreateListbox(const HWND parent, const HINSTANCE instance, DWORD style, 
        const RECT& rc, const int id, const ustring& caption)
	{
		style |= WS_CHILD | WS_VISIBLE;
		return CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", caption.c_str(), style, 
            rc.left, rc.top, rc.right, rc.bottom, parent, 
            reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, 0);
	}

	HWND CreateStatic(const HWND parent, const HINSTANCE instance, DWORD style, const RECT& rc, 
		const int id, const ustring& caption)
	{
		style |= WS_CHILD | WS_VISIBLE /*| SS_BLACKFRAME*/;
		return CreateWindowEx(0, "static", caption.c_str(), style, rc.left, rc.top, 
            rc.right, rc.bottom, parent, 
            reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, 0);
	}

    HWND CreateButton(const HWND parent, const HINSTANCE instance, DWORD style, const RECT& rc, 
        const int id, const ustring& caption)
    {
        style |= WS_CHILD | WS_VISIBLE;
        return CreateWindowEx(0, "button", caption.c_str(), style, rc.left, rc.top, rc.right,
            rc.bottom, parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, 0);
    }

    HWND CreateCombobox(const HWND parent, const HINSTANCE instance, DWORD style, const RECT& rc, 
        const int id, const ustring& caption)
    {
        style |= WS_CHILD|WS_VISIBLE;
        return CreateWindowEx(0,"combobox", caption.c_str(), style, rc.left, rc.top, rc.right,
            rc.bottom, parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, 0); 
    }

    HWND CreateEditBox(const HWND parent, const HINSTANCE instance, DWORD style, const RECT& rc,
        const int id, const ustring& caption)
    {
        style |= WS_CHILD | WS_VISIBLE;
        return CreateWindowEx(WS_EX_CLIENTEDGE, "edit", caption.c_str(), style, rc.left, rc.top, rc.right,
            rc.bottom, parent, reinterpret_cast<HMENU>(static_cast<INT_PTR>(id)), instance, 0);
    }
};

#endif
