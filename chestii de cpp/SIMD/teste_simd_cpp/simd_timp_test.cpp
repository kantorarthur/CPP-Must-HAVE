#include <experimental/simd>
#include <benchmark/benchmark.h>
#include <vector>
__attribute__((optimize("no-tree-vectorize")))
void functie_slow(const std::vector<float>& vec1,
                  const std::vector<float>& vec2,
                  std::vector<float>& vec3)
{
    for(auto i{0uz}; i < vec1.size(); ++i)
        vec3[i] = vec1[i] + vec2[i];
}

void functie_simd(const std::vector<float>& vec1,
                  const std::vector<float>& vec2,
                  std::vector<float>& vec3)
{
    using V = std::experimental::native_simd<float>;
    constexpr std::size_t simd_size = V::size();

    std::size_t i{};
    for(; i + simd_size <= vec1.size(); i += simd_size)
    {
        V x(&vec1[i], std::experimental::element_aligned);
        V y(&vec2[i], std::experimental::element_aligned);

        V z = x + y;

        z.copy_to(&vec3[i], std::experimental::element_aligned);
    }

    for(; i < vec1.size(); ++i)
        vec3[i] = vec1[i] + vec2[i];
}

static void benchmark_slow(benchmark::State& state)
{
    const std::size_t n = static_cast<std::size_t>(state.range(0));
    std::vector<float> a(n, 2.0f), b(n, 5.0f), out(n);

    for (auto _ : state) {
        functie_slow(a, b, out);
        benchmark::DoNotOptimize(out.data());
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(n));
}
BENCHMARK(benchmark_slow) -> Arg(5'000'000);

static void benchmark_simd(benchmark::State& state)
{
    const std::size_t n = static_cast<std::size_t>(state.range(0));
    std::vector<float> a(n, 2.0f), b(n, 5.0f), out(n);

    for (auto _ : state) {
        functie_simd(a, b, out);
        benchmark::DoNotOptimize(out.data());
        benchmark::ClobberMemory();
    }

    state.SetItemsProcessed(
        static_cast<int64_t>(state.iterations()) * static_cast<int64_t>(n));
}
BENCHMARK(benchmark_simd)->Arg(5'000'000);

BENCHMARK_MAIN();

