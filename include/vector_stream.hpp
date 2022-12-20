#include <vector>
#include <stdexcept>
#include "lexer.hpp"

#ifndef ARM_VECTOR_STREAM_HPP
#define ARM_VECTOR_STREAM_HPP

namespace ARM::VectorStream {
    template<typename T>
    class vector_stream {
    public:
        vector_stream() = default;
        ~vector_stream() = default;
        explicit vector_stream(std::vector<T> &vector) { std::copy(vector.begin(), vector.end(),
                                                                   std::back_inserter(this->vector)); }

        void set_vector(std::vector<T> &vec) { std::copy(vec.begin(), vec.end(), std::back_inserter(vector)); }

        void reset() {
            index = 0;
        }

        void append(T value) {
            vector.push_back(value);
        }

        void prepend(T value) {
            vector.insert(vector.begin(), value);
        }

        T pop() {
            if (index == vector.size()) {
                throw std::out_of_range("Cannot pop from empty vector_stream");
            }
            return get(index++);
        }

        T next() {
            if (has_next()) {
                return get(index++);
            }
            throw std::out_of_range("Index out of range");
        }

        T peek() {
            if (has_next()) {
                return get(index);
            }
            throw std::out_of_range("Index out of range");
        }

        bool has_next() {
            return index < vector.size();
        }

        T look_ahead(int offset) {
            if (index + offset < vector.size()) {
                return get(index + offset);
            }
            throw std::out_of_range("Index out of range");
        }

    private:
        std::vector<T> vector;
        int index = 0;

        T get(int index) {
            return vector.at(index);
        }
    };
}

#endif //ARM_VECTOR_STREAM_HPP
