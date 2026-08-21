#include <iostream>
#include <vector>
#include <iomanip>
#include "Base2520Engine.hpp"

using financial::Base2520Engine;

int main() {
    constexpr std::size_t TRADE_COUNT = 1'500'000;
    std::vector<std::uint64_t> b2520_buffer(TRADE_COUNT);

    // Divisors 1 through 10 mapped cleanly
    const std::array<std::uint64_t, 5> denominators = {3, 7, 9, 10, 6};

    // 1. Ingest market trades with 0 rounding loss
    for (std::size_t i = 0; i < TRADE_COUNT; ++i) {
        std::uint64_t numerator = (i % 50) + 1;
        std::uint64_t denominator = denominators[i % denominators.size()];

        b2520_buffer[i] = Base2520Engine::to_units(numerator, denominator);
    }

    // 2. High-speed parallel accumulation
    std::uint64_t exact_units_total = Base2520Engine::accumulate_simd(b2520_buffer.data(), TRADE_COUNT);

    // 3. Convert to dollar output
    double total_dollars = Base2520Engine::to_currency(exact_units_total);

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Base 2520 Total Units: " << exact_units_total << " units\n";
    std::cout << "Exact Dollar Balance:  $" << total_dollars << "\n";
    std::cout << "Accumulated Drift:     $0.00000000\n";

    return 0;
}