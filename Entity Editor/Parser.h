#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

class BaseFileType;
class Entity;
typedef std::shared_ptr<Entity> entity_ptr;

namespace parsing 
{
    enum FileType { TEXT, JSON, XML };

    template <class T>
    void Read(const char * filename, std::vector<T>& data);
    
    template <class T>
    void Write(const char * filename, std::vector<T>& data);

    BaseFileType* FileTypeFactory(const FileType ft);
};

class Parser
{
public:
    Parser();
    Parser(const Parser& p);
    ~Parser(void);

    void Read(const char * filename, std::vector<entity_ptr>& data);
    void Write(const char * filename, std::vector<entity_ptr>& data);

private:
    std::shared_ptr<BaseFileType> current_file;
};

#endif
