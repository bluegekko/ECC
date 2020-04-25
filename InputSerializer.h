#ifndef INPUTSERIALIZER_H_INCLUDED
#define INPUTSERIALIZER_H_INCLUDED

#include <fstream>
#include <vector>
#include <sstream>

const char COMMENT_CHAR = '#';

class InputSerializer
{
public:
    InputSerializer(std::string fileName) : fileName(fileName), index(0) {}
    void initialize()
    {
        std::ifstream inputStream(fileName);
        while(!inputStream.eof()) {
            std::string temp;
            inputStream >> temp;
            inputs.push_back(temp);
        }
    }
    uint64_t getNextNumber()
    {
        do
        {
            std::string temp = inputs[index++];
            if(temp[0] == COMMENT_CHAR)
            {
                continue;
            }
            uint64_t returnValue;
            std::istringstream(temp) >> returnValue;
            // TODO exception if not a number
            return returnValue;
        } while (index < inputs.size());
        throw 1; // TODO exception handling.
    }
private:
    std::string fileName;
    std::vector<std::string> inputs;
    uint64_t index;
};

#endif // INPUTSERIALIZER_H_INCLUDED
