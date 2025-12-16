#ifndef files_h
#define files_h

#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

struct Toy {
    char name[50];
    double price;
    uint8_t minAge;
    uint8_t maxAge;
    bool isDoll;

    Toy() : price(0.0), minAge(0), maxAge(0), isDoll(false) {
        fill_n(name, 50, '\0');
    }

    Toy(const string& n, double p, uint8_t minA, uint8_t maxA, bool doll = false) : price(p), minAge(minA), maxAge(maxA), isDoll(doll) {
        size_t length = min(n.size(), size_t(49));
        std::copy_n(n.c_str(), length, name);
        name[length] = '\0';
    }
};

class LabFile {
    private:
        static int generateRandom(int min, int max);

    public:
        static void fillWithRandom(const string& filename, int count, int min = 1, int max = 100);

        static int findDiff(const string& filename);

        static void displayFile(const string& filename);

        static void createToyFile(const string& filename);

        static Toy createToy();

        static void addToyToFile(const string& filename);

        static double calculateDoll(const string& filename, int targetAge);

        static void printToy(const Toy& toy);


};

#endif

