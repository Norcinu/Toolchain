#ifndef FILE_POLICIES_H
#define FILE_POLICIES_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <Windows.h>

#include "FileOperations.h"
#include "../Shared/rapidxml/rapidxml.hpp"

struct PolicyType 
{
    static const int APPEND = 1;
    static const int READ = 2;
    static const int WRITE = 3;
};

struct BasePolicy
{
    std::vector<Entity*> entities; // change this when entity class is written.
    std::string filename;

    virtual ~BasePolicy() 
    {
        for (auto i = entities.begin(); i!=entities.end(); ++i)
            delete *i;

        entities.clear();
    }

    virtual void read() = 0;
    virtual void write() = 0;
    virtual void append() = 0;
};

struct XmlPolicy : public BasePolicy
{
    void append() {}
    void read() {} 
    void write() {} 
};

struct TextPolicy : public BasePolicy
{
    void append()
    { 
        OutputDebugString("running textpolicy::append.\n");
    }

    void read() 
    {
        std::ifstream file(filename);
        if (file.is_open())
        {

        }
        else
            std::cerr << "Error loading file.\n";
    } 

    void write() 
    {

    } 
};

struct JsonPolicy : public BasePolicy
{
    void append() {}
    void read() {} 
    void write() {} 
};

// Load files and save state.
//class PolicyFileType
//{
//public:
//    virtual ~PolicyFileType() {}
//    virtual void LoadFile(const std::string& filename) = 0;
//
//    std::vector<Entity*> entities;
//protected:
//    PolicyFileType() {}
//    PolicyFileType(const std::string& filename) {}
//};
//
//class TextFilePolicy : public PolicyFileType
//{
//public:
//    TextFilePolicy() {}
//    TextFilePolicy(const std::string& filename);
//    ~TextFilePolicy() {}
//
//    void LoadFile( const std::string& filename );
//};
//
//class XmlFilePolicy : public PolicyFileType
//{
//public:
//    XmlFilePolicy() {}
//    XmlFilePolicy(const std::string& filename);
//    ~XmlFilePolicy() {}
//    
//    void LoadFile( const std::string& filename );
//};
//
//class JsonFilePolicy : public PolicyFileType
//{
//public:
//    JsonFilePolicy() {}
//    JsonFilePolicy(const std::string& filename);
//    ~JsonFilePolicy() {}
//
//    void LoadFile( const std::string& filename );
//};
//
//struct ActionPolicyTextWrite
//{
//    template <typename FileType>
//    void DoAction(FileType file)
//    {
//
//    }
//};
//
//struct ActionPolicyTextAppend
//{
//    template <typename FileType>
//    void DoAction(FileType file)
//    {
//
//    }
//};
//
//struct ActionPolicyTextRead
//{
//    template <typename FileType>
//    void DoAction(FileType file)
//    {
//
//    }
//};


#endif