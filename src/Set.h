#ifndef U_S__HOUSING_FINDER_1_0_SET_H
#define U_S__HOUSING_FINDER_1_0_SET_H
#include "Listing.h"
#include <climits>
#include <fstream>
#include <sstream>
#include <chrono>
#include <functional>


class Set{
private:
    struct Node{
        Listing data;
        Node* next;
        Node(Listing& listing);
    };
    Node** buckets;
    int numEntries;
    int numBuckets;
    double loadFactor;
    const double maxLoadFactor = 1.0;

    unsigned long long hashFunc(string& id);
    int reduce(unsigned long long hashCode);
    void resize();
    void searchTable(const function<bool(Listing&)>& matches, int& numFound);
    Set(const Set&);
    Set& operator=(const Set&);
public:
    Set();
    ~Set();
    void insert(Listing& listing);
    void readInData();
    void searchByMonthlyRent(int monthlyRentLower, int monthlyRentUpper);
    void searchByType(string& type);
    void searchBySqFeet(int sqfeetLower, int sqfeetUpper);
    void searchByNumBeds(int beds);
    void searchByNumBaths(double baths);
    void searchByState(string& state);
    void printAll();
};

#endif