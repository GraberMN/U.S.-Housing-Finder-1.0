#ifndef U_S__HOUSING_FINDER_1_0_SET_H
#define U_S__HOUSING_FINDER_1_0_SET_H
#include "Listing.h"
#include <set>
#include <climits>
#include <fstream>
#include <sstream>
#include <chrono>

struct ListingCompare{
    bool operator()(const Listing& a, const Listing& b) const{
        return a.id < b.id;
    }
};

class Set{
private:
    set<Listing, ListingCompare> listings;
public:
    Set();
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