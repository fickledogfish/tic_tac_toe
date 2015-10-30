#include "random.hpp"

int rnd::random_int(int min, int max) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(rng);
}
