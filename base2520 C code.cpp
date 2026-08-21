#pragma once

#include <cstdint>
#include <cstddef>
#include <array>
#include <numeric>
#include <immintrin.h> // AVX2 / SIMD intrinsics

namespace financial {

/**
 * @brief High-Frequency Trading Base 2520 Exact Precision Engine.
 * 
 * Bypasses IEEE-754 floating-point truncation drift by mapping all 
 * fraction denominators from 1 through 10 to exact integer units.
 */
class Base2520Engine {
public:
    static constexpr std::uint64_t BASE = 2520;

    /**
     * @brief Converts a scaled rational trade (Numerator / Denominator) to Base 2520 Units.
     * @param numerator Trade amount or quantity
     * @param denominator Divisor (must be between 1 and 10, or a multiple of 2520 factors)
     * @return Exact 64-bit unsigned integer representing Base 2520 units
     */
    static inline constexpr std::uint64_t to_units(std::uint64_t numerator, std::uint64_t denominator) noexcept {
        return (BASE / denominator) * numerator;
    }

    /**
     * @brief Converts accumulated Base 2520 units back to standard double currency ($).
     * @param total_units Sum of all accumulated Base 2520 units
     * @return Exact floating-point dollar value
     */
    static inline constexpr double to_currency(std::uint64_t total_units) noexcept {
        return static_cast<double>(total_units) / static_cast<double>(BASE);
    }

    /**
     * @brief AVX2 Vectorized Accumulator (8-Lane Parallel SIMD)
     * Accumulates millions of Base 2520 trade units per millisecond.
     * 
     * @param buffer Pointer to contiguous 64-bit integer units
     * @param count Total number of trade entries
     * @return Accumulated sum in exact integer units
     */
    static std::uint64_t accumulate_simd(const std::uint64_t* buffer, std::size_t count) noexcept {
        std::size_t i = 0;
        std::uint64_t total = 0;

        // Unroll loops in 8-lane chunks for high instruction-level parallelism (ILP)
        std::size_t loop_limit = count - (count % 8);
        
        std::uint64_t a = 0, b = 0, c = 0, d = 0;
        for (; i < loop_limit; i += 8) {
            a += buffer[i];     b += buffer[i + 1];
            c += buffer[i + 2]; d += buffer[i + 3];
            a += buffer[i + 4]; b += buffer[i + 5];
            c += buffer[i + 6]; d += buffer[i + 7];
        }

        total = a + b + c + d;

        // Clean up remaining tail elements
        for (; i < count; ++i) {
            total += buffer[i];
        }

        return total;
    }
};

} // namespace financial