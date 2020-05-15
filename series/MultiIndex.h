#ifndef MULTIINDEX_H_INCLUDED
#define MULTIINDEX_H_INCLUDED

#include <vector>

namespace series
{

class MultiIndex
{
public:
    MultiIndex(std::size_t limit, std::size_t indexSize) : limit(limit), indexSize(indexSize), valid(true)
    {
        indices.resize(indexSize);
        size_t value = 0;
        for (size_t& index : indices)
        {
            index = value++;
        }
        if (value>limit)
        {
            value = false;
        }
    }
    void increment()
    {
        size_t backwardIndex = 1;
        valid = false;
        while(backwardIndex <= indexSize)
        {
            indices[indexSize - backwardIndex]++;
            if (indices[indexSize - backwardIndex] + backwardIndex  > limit )
            {
                backwardIndex++;
            }
            else
            {
                while(backwardIndex > 0)
                {
                    backwardIndex--;
                    indices[indexSize - backwardIndex] = indices[indexSize - backwardIndex - 1] + 1;
                }
                valid = true;
                return;
            }
        }
    }
    bool isValid()
    {
        return valid;
    }
    ~MultiIndex() = default;
    std::vector<size_t>& getIndices() {return indices;}
private:
    std::vector<size_t> indices;
    std::size_t limit;
    std::size_t indexSize;
    bool valid;
};

int calculateMultiplicationAtIndex(std::vector<int>& series, MultiIndex& multiIndex, size_t startIndex)
{
    int value = 1;
    for(size_t& index : multiIndex.getIndices())
    {
        value*=series[startIndex + index - 1];
    }
    return value;
}


}

#endif // MULTIINDEX_H_INCLUDED
