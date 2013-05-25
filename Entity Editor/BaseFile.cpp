#include "BaseFile.h"
#include "Parser.h"

FileIO::FileIO() :
    parser(nullptr) {}

FileIO::FileIO(Parser * p) : 
    parser(p) {}