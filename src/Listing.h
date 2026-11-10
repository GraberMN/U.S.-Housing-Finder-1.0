//
// Created by grabe on 11/9/2026.
//

#ifndef U_S_HOUSING_FINDER_1_0_LISTING_H
#define U_S_HOUSING_FINDER_1_0_LISTING_H

#include <iostream>
#include <string>
using namespace std;

// Each listing in the dataset is represented as a Listing object
class Listing
{
public:
    string id;
    string url;
    int monthlyRent;
    string type;
    int sqfeet;
    int beds;
    double baths;
    string state;
};


#endif //U_S_HOUSING_FINDER_1_0_LISTING_H
