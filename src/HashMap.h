//
// Created by grabe on 11/12/2026.
//

#ifndef U_S__HOUSING_FINDER_1_0_HASHMAP_H
#define U_S__HOUSING_FINDER_1_0_HASHMAP_H

#include "Listing.h"
#include <utility>
#include <climits>
#include <fstream>
#include <sstream>
#include <chrono>

// Each key value pair in the HashMap consists of a unique key (listing ID) and a value (Listing object).
// The HashMap has an initial bucket count of 5, has a max load factor of 0.8, and uses linear probing for collisions.
class HashMap
{
private:
    pair<string, Listing>* hashTable;
    int numEntries;
    int numBuckets;
    double loadFactor;
    const double maxLoadFactor = 0.8;

    long long hashFunc(string& id);
    int reduce(long long hashCode);
    void resize();
    int linearProbing(int index);
public:
    HashMap();
    ~HashMap();
    void insert(Listing& listing);
    void readInData();
    void searchByMonthlyRent(int monthlyRentLower, int monthlyRentUpper);
    void searchByType(string& type);
    void searchBySqFeet(int sqfeet);
    void searchByNumBeds(int beds);
    void searchByNumBaths(double baths);
    void searchByState(string& state);
    void printAll();
};


#endif //U_S__HOUSING_FINDER_1_0_HASHMAP_H
