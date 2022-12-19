#include "converter.hpp"

namespace ARM
{
    namespace Converters
    {
        // Convert a uint32 to a float as per IEEE754 for floating point numbers
        float uint32_to_float(uint32_t word)
        {
            bool sign = word & 0x80000000;
            uint32_t exponent = (word & 0x7F800000) >> 23;
            uint32_t mantissa = word & 0x007FFFFF;
            float result = 0.0f;
            if (exponent == 0xFF)
            {
                if (mantissa == 0)
                {
                    result = INFINITY;
                }
                else
                {
                    result = NAN;
                }
            }
            else if (exponent == 0)
            {
                if (mantissa == 0)
                {
                    result = 0.0f;
                }
                else
                {
                    result = ldexpf(mantissa, -149);
                }
            }
            else
            {
                result = ldexpf(mantissa + 0x00800000, exponent - 150);
            }
            return sign ? -result : result;
        }

        // Convert a uint64 to a double as per IEEE754 for double precision floating point numbers
        double uint64_to_double(uint64_t xword)
        {
            bool sign = xword & 0x8000000000000000;
            int32_t exponent = (xword & 0x7FF0000000000000) >> 52;
            uint64_t mantissa = xword & 0x000FFFFFFFFFFFFF;
            double result = 0.0;
            if (exponent == 0x7FF)
            {
                if (mantissa == 0)
                {
                    result = INFINITY;
                }
                else
                {
                    result = NAN;
                }
            }
            else if (exponent == 0)
            {
                if (mantissa == 0)
                {
                    result = 0.0;
                }
                else
                {
                    result = ldexp(mantissa, -1074);
                }
            }
            else
            {
                result = ldexp(mantissa + 0x0010000000000000, exponent - 1075);
            }
            return sign ? -result : result;
        }

        // Convert two uint32 to a double as per IEEE754 for double precision floating point numbers
        double uint32_to_double(uint32_t word_1, uint32_t word_2)
        {
            return uint64_to_double((static_cast<uint64_t>(word_1) << 32) | word_2);
        }

    } // namespace Converters
} // namespace ARM
