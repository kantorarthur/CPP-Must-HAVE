#include <iostream>
#include <string_view>
#include <meta>

enum class Test
{
    vaca,
    gaina,
    mata
};

template<class T>
constexpr std::string_view enum_to_string(T var)
{
    std::string_view result = "<unknown>";

    template for(constexpr auto e : std::define_static_array(std::meta::enumerators_of(^^T)))
    {
        if(var == [:e:])
            result = std::meta::identifier_of(e);
    }
    return result;
}

int main()
{
    std::cout << enum_to_string(Test::vaca);
}

