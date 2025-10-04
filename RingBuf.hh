#include <cstddef>
#include <cstdio>
#include <stdexcept>
#include <vector>

namespace dkdsp {
    template <typename T> class DRingBuf {
        public:
        DRingBuf<T>(std::size_t size) :
        read(0),
        write(size),
        count(0),
        max(size)
        {
            data.resize(size);
            max = size;
        }
        void push(T item) {
            if (is_full()) throw std::runtime_error("Buffer is full");
            data[write] = item;
            write = (write + 1) % max;
            ++count;
        };
        T pop() {
            if (is_empty()) throw std::runtime_error("Is empty");
            T item = data[read];
            T empty_item;
            count--;
            data[read] = empty_item;
            read = (read + 1) % max;
            return item;
        }
        T get(size_t index) {return data[(read+index)%max];};
        T get_from_tail(size_t index) {return data[(write-index)%max];};
        T front() { return data[read]; };
        size_t size() {return count;};
        bool is_empty() {return count == 0;};
        bool is_full() { return max == count; };


        private:
        std::vector<T> data;
        size_t read;
        size_t write;
        size_t max;
        size_t count;

    };
}
