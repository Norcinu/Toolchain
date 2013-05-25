#ifndef BASE_FILE_H
#define BASE_FILE_H

#include <vector>

class Parser;

class FileIO
{
public:
    enum FileType { JSON, XML, TEXT };
    
    FileIO();
    FileIO(Parser * p);
    ~FileIO();

    template <class DataSet>
    void Read(const char * filename, std::vector<DataSet>& data);
    
    template <class DataSet>
    void Write(const char * filename, std::vector<DataSet>& data);

private:
    Parser * parser;
};

template <class DataSet>
void FileIO::Read(const char * filename, std::vector<DataSet>& data) {
    parser->Read(filename, data);
}

template <class DataSet>
void FileIO::Write(const char * filename, std::vector<DataSet>& data) {
    parser->Write(filename, data);
}

#endif
