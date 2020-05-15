#ifndef INPUTSERIALIZER_H_INCLUDED
#define INPUTSERIALIZER_H_INCLUDED

#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cstdlib>

const char SPECIAL_CHAR = '#';

uint64_t convertStringToInt(std::string value)
{
    uint64_t returnValue = 0;
    std::istringstream(value) >> returnValue;
    return returnValue;
}

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
    void initializeMap()
    {
        std::ifstream inputStream(fileName);
        std::string currentKey = "";
        while(!inputStream.eof()) {
            std::string temp;
            inputStream >> temp;
            if (temp[0] == SPECIAL_CHAR)
            {
                currentKey = temp;
            }
            else if (temp != "")
            {
                inputMap[currentKey].push_back(temp);
            }

        }
    }
    uint64_t getNextNumber()
    {
        do
        {
            std::string temp = inputs[index++];
            if(temp[0] == SPECIAL_CHAR)
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
    uint64_t getNumberForKey(std::string key, size_t index = 0)
    {
        uint64_t returnValue = 0;
        if (inputMap[key].size() < index + 1)
        {
            std::cout << "mandatory parameter missing: " << key << "!" << std::endl;
            std::exit(-1);
        }
        std::istringstream(inputMap[key][index]) >> returnValue;
        return returnValue;
    }
    std::string getStringForKey(std::string key, size_t index = 0)
    {
        if (inputMap[key].size() < index + 1)
        {
            std::cout << "mandatory parameter missing: " << key << "!" << std::endl;
            exit(-1);
        }
        return inputMap[key][index];
    }
    std::vector<std::string> getStringVectorForKey(std::string key)
    {
        if (inputMap[key].size() == 0)
        {
            std::cout << "mandatory parameter missing: " << key << "!" << std::endl;
            exit(-1);
        }
        return inputMap[key];
    }
    std::pair<uint64_t, uint64_t> getNumberPairForKey(std::string key)
    {
        return std::pair<uint64_t, uint64_t>(getNumberForKey(key, 0), getNumberForKey(key, 1));
    }
private:
    std::string fileName;
    std::vector<std::string> inputs;
    std::map<std::string, std::vector<std::string>> inputMap;
    uint64_t index;
};


#endif // INPUTSERIALIZER_H_INCLUDED
