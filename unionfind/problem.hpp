#pragma once
#include <fstream>

#include "../utils/random.hpp"
namespace libtest {
struct unionfind
{
    static constexpr const char* path       = "unionfind";
    static constexpr const char* name       = "Union Find Tree";
    static constexpr std::size_t time_limit = 2000;
    template<typename constraints>
    static void generate_input(std::ofstream& input_file)
    {
        constexpr usize n_min = constraints::n_min, n_max = constraints::n_max;
        constexpr usize q_min = constraints::q_min, q_max = constraints::q_max;
        const usize n = g_rng.uniform_int(n_min, n_max), q = g_rng.uniform_int(q_min, q_max);
        input_file << n << " " << q << "\n";
        for (usize i = 0; i < q; i++) {
            const usize type = g_rng.uniform_int(0UL, 2UL);
            if (type == 0) {
                input_file << "0 " << g_rng.uniform_int(0UL, n - 1) << " " << g_rng.uniform_int(0UL, n - 1) << "\n";
            } else if (type == 1) {
                input_file << "1 " << g_rng.uniform_int(0UL, n - 1) << " " << g_rng.uniform_int(0UL, n - 1) << "\n";
            } else {
                input_file << "2 " << g_rng.uniform_int(0UL, n - 1) << "\n";
            }
        }
    }
    static void generate_output(std::ifstream& input_file, std::ofstream& output_file)
    {
        usize n, q;
        input_file >> n >> q;
        std::vector<usize> ans;
        std::vector<usize> id(n);
        std::iota(id.begin(), id.end(), 0);
        for (usize i = 0; i < q; i++) {
            usize type;
            input_file >> type;
            if (type == 0) {
                usize a, b;
                input_file >> a >> b;
                if (id[a] != id[b]) {
                    const usize aid = id[a], bid = id[b];
                    for (usize i = 0; i < n; i++) {
                        if (id[i] == bid) { id[i] = aid; }
                    }
                }
            } else if (type == 1) {
                usize a, b;
                input_file >> a >> b;
                ans.push_back(static_cast<usize>(id[a] == id[b]));
            } else {
                usize ind;
                input_file >> ind;
                usize sum = 0;
                for (usize i = 0; i < n; i++) {
                    if (id[i] == id[ind]) { sum++; }
                }
                ans.push_back(sum);
            }
        }
        output_file << ans.size() << "\n";
        for (const auto e : ans) { output_file << e << "\n"; }
    }
    static bool judge(std::ifstream& /* input_file */, std::ifstream& generated_output_file, std::ifstream& solution_output_file)
    {
        usize q_actual, q_output;
        generated_output_file >> q_actual;
        solution_output_file >> q_output;
        if (q_actual != q_output) { return false; }
        for (usize i = 0; i < q_actual; i++) {
            ll actual, output;
            generated_output_file >> actual;
            solution_output_file >> output;
            if (actual != output) { return false; }
        }
        return true;
    }

    struct small_constraints
    {
        static constexpr usize n_min = 1, n_max = 100;
        static constexpr usize q_min = 1, q_max = 100;
    };
    struct large_constraints
    {
        static constexpr usize n_min = 1, n_max = 100000;
        static constexpr usize q_min = 1, q_max = 100000;
    };
};
}  // namespace libtest
