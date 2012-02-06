#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <vector>

struct Entity
{
    void operator=(const Entity* ent) { *this = ent; }
};

//        xml/json/text            Read/Write/Append. // was int
template <typename FileTypePolicy, int ActionPolicy> 
class FileOperations : public FileTypePolicy
{
public:
    FileOperations() 
    {
      
    }

    ~FileOperations(void) {}

    void Run(const char * filename, std::vector<Entity*>& entities)
    {
        switch(ActionPolicy)
        {
        case PolicyType::APPEND:
            Append(filename, entities);
            break;
        case PolicyType::READ:
            Read(filename, entities);
            break;
        case PolicyType::WRITE:
            Write(filename, entities);
            break;
        }
    }

    using FileTypePolicy::entities;
    using FileTypePolicy::filename;
    using FileTypePolicy::append;

private:
    void Append(const char * filename_, std::vector<Entity*>& entities_) 
    {
        entities = entities_;
        filename = filename_;
        append();
    }
    
    void Read(const char * filename_, std::vector<Entity*>& entities_) 
    {
        /*  FileTypePolicy::filename = filename;
        FileTypePolicy::Read();
        entities = FileTypePolicy::entities;*/
    }
    
    void Write(const char * filename, std::vector<Entity*>& entities) 
    {
        /*FileTypePolicy::entities = entities;
        FileTypePolicy::filename = filename;
        FileTypePolicy::Write();*/
    }
};

#endif
