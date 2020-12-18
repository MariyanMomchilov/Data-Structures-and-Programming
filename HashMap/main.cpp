#include "map.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include <string>

auto hashF = [](const std::string& str) -> size_t
    {
        size_t sum = 0;
        for (char c: str)
            sum += (size_t)c;
        return sum;
    };

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
}



int main()
{
    doctest::Context().run();
    return 0;
}

