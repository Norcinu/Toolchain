#include <Windows.h>
#include "Framework.h"
#include "FilePolicies.h"
#include "FileOperations.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationFramework app(hInstance);
	if (app.Init())
	{
		app.Run();
		app.Shutdown();
	}
   
    typedef FileOperations<TextPolicy, PolicyType::APPEND> TextFileAppend;
    typedef FileOperations<TextPolicy, PolicyType::READ> TextFileReader;
    typedef FileOperations<TextPolicy, PolicyType::WRITE> TextFileWriter;
    
    std::vector<Entity*> ents;
    TextFileAppend test;
    test.Run("cunt.txt", ents);
    
    return 0;
}
