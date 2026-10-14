#include <experimental/simd>
#include <vector>
#include <print>

void add_vectors_simd(const std::vector<float>& vec1
                      ,const std::vector<float>& vec2
                      ,std::vector<float>& vec3)
{
    using V = std::experimental::native_simd<float>;
    constexpr std::size_t simd_size = V::size();
    //Aici practic verific cate float-uri poate sa proceseze procesoru simultan
    //
    //Apoi salvez nr ala in "simd_size"

    size_t n{vec1.size()};
    size_t i{};

    std::println("Se pot procesa {} valori simultan", simd_size);

    for(; i + simd_size < n; i += simd_size)
    {
        V x(&vec1[i], std::experimental::element_aligned);
        V y(&vec2[i], std::experimental::element_aligned);

        V z = x + y;
        z.copy_to(&vec3[i], std::experimental::element_aligned);
    }
    std::println("Aici i este: {}", i);
    //aici mai adaugam elementele care poate n-au fost procesate(la final)
    for(; i < n; ++i)
        vec3[i] = vec1[i] + vec2[i];
    for(i = 0; i < n; ++i)
        std::println("{}", vec3[i]);
}

int main()
{
    std::vector<float> vec1(10, 2);
    std::vector<float> vec2(10, 5);
    std::vector<float> vec3(10, 0);

    add_vectors_simd(vec1, vec2, vec3);
    return 0;
}
