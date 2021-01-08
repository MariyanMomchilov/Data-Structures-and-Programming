#include "map.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <string>
#include <fstream>
#include "zadachi.h"

TEST_CASE("Map<string, int>")
{
    Map<std::string, int> m(hashF, 5);

    CHECK(!m.hasKey("husky"));
    m["husky"];
    CHECK(m.hasKey("husky"));
    m["husky"] = 10;
    CHECK(m["husky"] == 10);
    
}

TEST_CASE("Iterator")
{
     Map<std::string, int> m(hashF, 5);

    m["frenchie"] = 3;
    m["cane corso"] = 50;
    m["american staffordshire terrier"] = 10;
    m["malteser"] = 50;
    m["kangal"] = 8;

    for (std::string key: m)
    {
        std::cout << "Hash of \"" << key << "\" = " << hashF(key) % 5 << ", ";
        std::cout << "Map[" << key << "] = " << m[key] << '\n';
    }
    std::cout << '\n';

    std::ofstream f("file.txt");
    f << m;

}

TEST_CASE("ZADACHI")
{
    const char *text1 = "In computing, a hash table (hash map) is a data structure used to implement "
                        "an associative array, a structure that can map keys to values. A hash table "
                        "uses a hash function to compute an index into an array of buckets or slots, "
                        "from which the correct value can be found.";

    const char *text2 = "Ideally, the hash function will assign each key to a unique bucket, but this "
                        "situation is rarely achievable in practice (usually some keys will hash to the "
                        "same bucket)";
                        
    sameWords(text1, text2);
}

TEST_CASE("Copy OPs")
{
     Map<std::string, int> m(hashF, 5);

    m["frenchie"] = 3;
    m["cane corso"] = 50;
    m["american staffordshire terrier"] = 10;
    m["malteser"] = 50;
    m["kangal"] = 8;

    CHECK(m.changeKey("american staffordshire terrier", ""));
    CHECK(m.changeKey("asdf", "") == false);

    Map<std::string, int> m2 = m;
    for (std::string key: m2)
    {
        std::cout << "Hash of \"" << key << "\" = " << hashF(key) % 5 << ", ";
        std::cout << "Map[" << key << "] = " << m2[key] << '\n';
    }
}


int main()
{
    doctest::Context().run();
    return 0;
}

