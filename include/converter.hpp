#include <stdint.h>
#include <cmath>

namespace ARM
{
    namespace Converters
    {
        float uint32_to_float(uint32_t value);
        double uint32_to_double(uint32_t value_1, uint32_t value_2);
        double uint64_to_double(uint64_t value);
    } // namespace Converters
    
} // namespace ARM
