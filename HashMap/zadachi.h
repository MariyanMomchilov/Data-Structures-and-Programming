#include "map.h"
#include <string>
#include <vector>
#include <unordered_set>

auto hashF = [](const std::string& str) -> size_t
    {
        size_t sum = 0;
        for (char c: str)
            sum += (size_t)c;
        return sum;
    };



void printWords(std::vector<std::string> &words)
{
    for (auto str: words)
        std::cout << str << '\n';
}

std::vector<std::string> extractWords(const char *text, std::unordered_set<char> separators = {' ', '\t', '.', ',', '!', '?', '(', ')'})
{
    std::vector<std::string> words;
    std::string crrWord;
    while (*text != 0)
    {
        while (separators.find(*text) == separators.end() && *text != 0)
        {
            crrWord += *text;
            text++;
        }
        if (crrWord != "")
        {
            words.push_back(crrWord);
            crrWord = "";
        }
        text++;
    }
    return words;
}

Map<std::string, size_t> sameWords(const char *t1, const char *t2)
{
    std::vector<std::string> wordsT1 = extractWords(t1);
    std::vector<std::string> wordsT2 = extractWords(t2);

    Map<std::string, size_t> result(hashF, wordsT1.size());

    std::unordered_set<std::string> set;

    for (auto w: wordsT1)
    {
        set.insert(w);
    }

    for (auto w: wordsT2)
    {
        if (set.find(w) != set.end())
        {
            if (result.hasKey(w))
                result[w]++;
            else
                result[w] = 1;
        }
    }

    for (std::string w: result)
    {
        std::cout << "word: " << w <<  " occured " << result[w] << " times" << '\n'; 
    }

    return result;
}
