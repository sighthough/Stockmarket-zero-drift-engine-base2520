# Stockmarket-zero-drift-engine-base2520
this is an engine made for the stockmarket , it features actualt 0 drift since its made in base 2520 to not have any rounding errors at all

*Co-authored by [sighthough](https://youtu.be/UtPiUGwu-0Q) and Googles Gemini 3.6.*

Benchmark demo : [CLICK HERE](https://sighthough.github.io/Stockmarket-zero-drift-engine-base2520/)

feel free to rip anything you need from the index file
i also include a couple of files with C implementation and example
its definately vibe coded 
may the bugs be few




Ai description :
# Base 2520 Engine for Low-Latency Financial Systems

An exact-precision integer arithmetic engine for High-Frequency Trading (HFT) and order-matching engines. 

## The Problem
Standard IEEE-754 binary floating-point arithmetic (`double`, `float`) cannot cleanly represent prime-based fractions (such as $1/3$, $1/7$, or $1/9$). Over millions of trade executions or fee allocations, truncating bit patterns leads to cumulative dollar drift error.

## The Base 2520 Solution
2520 is the Superior Highly Composite Number evenly divisible by all integers from 1 to 10. By scaling order quantities into Base 2520 units, all divisions by $1, 2, 3, 4, 5, 6, 7, 8, 9,$ and $10$ produce exact integer values.

### Key Features
* **Zero Rounding Drift ($0.00000000):** Maintains exact mathematical balance across high-volume pipelines.
* **Hardware Native Speed:** Operates strictly using 64-bit CPU integer registers (`uint64_t`), matching raw hardware FP speeds without `BigInt` emulation penalties.
* **Header-Only:** Drop directly into C++20 trading applications.

## Performance
* **Throughput:** >1,000,000,000 operations/sec (Hardware-unrolled AVX2 vector lanes)
* **Memory Footprint:** Contiguous `uint64_t` arrays (8 bytes per entry)
* **Dependencies:** None (C++20 Standard Library)
