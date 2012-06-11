#include <Windows.h>
#include "Framework.h"
#include "FilePolicies.h"
#include "FileOperations.h"
#include <json_spirit\json_spirit.h>
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationFramework app(hInstance);
	if (app.Init())
	{
		app.Run();
		app.Shutdown();
	}

	std::ifstream is("package.json");
	json_spirit::mValue v;
	
	json_spirit::read(is,v);
	json_spirit::mObject obj = v.get_obj();
	std::string s = obj["name"].get_str();
	OutputDebugString(s.c_str());
	std::string s2 = obj["main"].get_str();
	OutputDebugString("\n");
	OutputDebugString(s2.c_str());
	OutputDebugString("\n");

	typedef FileOperations<TextPolicy, PolicyType::APPEND> TextFileAppend;
    typedef FileOperations<TextPolicy, PolicyType::READ> TextFileReader;
    typedef FileOperations<TextPolicy, PolicyType::WRITE> TextFileWriter;
    
    std::vector<Entity*> ents;
    TextFileAppend test;
    test.Run("test.txt", ents);
    
    return 0;
}
