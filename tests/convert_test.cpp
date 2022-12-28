
#include "doctest.h"
#include "converter.hpp"

TEST_CASE("Convert a uint32 to a float") {
    SUBCASE("Positive Integer") {
        uint32_t value = 0x3F9E0652;
        float expected = 1.2345678806304931640625E0;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(result == expected);
    }
    SUBCASE("Negative Integer") {
        uint32_t value = 0xBF9E0652;
        float expected = -1.2345678806304931640625E0;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(result == expected);
    }
    SUBCASE("Positive Infinity") {
        uint32_t value = 0x7F800000;
        float expected = INFINITY;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(result == expected);
    }
    SUBCASE("Negative Infinity") {
        uint32_t value = 0xFF800000;
        float expected = -INFINITY;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(result == expected);
    }
    SUBCASE("Positive Zero") {
        uint32_t value = 0x00000000;
        float expected = 0.0f;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(result == expected);
    }
    SUBCASE("Negative Zero") {
        uint32_t value = 0x80000000;
        float expected = -0.0f;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(result == expected);
    }
    SUBCASE("Positive NaN") {
        uint32_t value = 0x7F800001;
        float expected = NAN;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(std::isnan(result));
    }
    SUBCASE("Negative NaN") {
        uint32_t value = 0xFF800001;
        float expected = NAN;
        float result = ARM::Converters::uint32_to_float(value);

        CHECK(std::isnan(result));
    }
}
TEST_CASE("Convert two uint32 to a double") {
    SUBCASE("Positive Double") {
        uint32_t value_1 = 0x3FF3C0CA;
        uint32_t value_2 = 0x4283DE1B;
        double expected = 1.23456789;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(result == expected);
    }
    SUBCASE("Negative Double") {
        uint32_t value_1 = 0xBFF3C0CA;
        uint32_t value_2 = 0x4283DE1B;
        double expected = -1.23456789;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(result == expected);
    }
    SUBCASE("Positive Infinity") {
        uint32_t value_1 = 0x7FF00000;
        uint32_t value_2 = 0x00000000;
        double expected = INFINITY;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(result == expected);
    }
    SUBCASE("Negative Infinity") {
        uint32_t value_1 = 0xFFF00000;
        uint32_t value_2 = 0x00000000;
        double expected = -INFINITY;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(result == expected);
    }
    SUBCASE("Positive Zero") {
        uint32_t value_1 = 0x00000000;
        uint32_t value_2 = 0x00000000;
        double expected = 0.0;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(result == expected);
    }
    SUBCASE("Negative Zero") {
        uint32_t value_1 = 0x80000000;
        uint32_t value_2 = 0x00000000;
        double expected = -0.0;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(result == expected);
    }
    SUBCASE("Positive NaN") {
        uint32_t value_1 = 0x7FF00000;
        uint32_t value_2 = 0x00000001;
        double expected = NAN;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(std::isnan(result));
    }
    SUBCASE("Negative NaN") {
        uint32_t value_1 = 0xFFF00000;
        uint32_t value_2 = 0x00000001;
        double expected = NAN;
        double result = ARM::Converters::uint32_to_double(value_1, value_2);

        CHECK(std::isnan(result));
    }
}
TEST_CASE("Convert a uint64 to a double") {
    SUBCASE("Positive Double") {
        uint64_t value = 0x3FF3C0CA4283DE1B;
        double expected = 1.23456789;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(result == expected);
    }
    SUBCASE("Negative Double") {
        uint64_t value = 0xBFF3C0CA4283DE1B;
        double expected = -1.23456789;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(result == expected);
    }
    SUBCASE("Positive Infinity") {
        uint64_t value = 0x7FF0000000000000;
        double expected = INFINITY;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(result == expected);
    }
    SUBCASE("Negative Infinity") {
        uint64_t value = 0xFFF0000000000000;
        double expected = -INFINITY;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(result == expected);
    }
    SUBCASE("Positive Zero") {
        uint64_t value = 0x0000000000000000;
        double expected = 0.0;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(result == expected);
    }
    SUBCASE("Negative Zero") {
        uint64_t value = 0x8000000000000000;
        double expected = -0.0;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(result == expected);
    }
    SUBCASE("Positive NaN") {
        uint64_t value = 0x7FF0000000000001;
        double expected = NAN;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(std::isnan(result));
    }
    SUBCASE("Negative NaN") {
        uint64_t value = 0xFFF0000000000001;
        double expected = NAN;
        double result = ARM::Converters::uint64_to_double(value);

        CHECK(std::isnan(result));
    }
}