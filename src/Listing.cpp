//
// Created by grabe on 11/9/2026.
//

#include "Listing.h"

// Listing constructor
Listing::Listing(string& _id, string& _url, int _monthlyRent, string& _type, int _sqfeet, int _beds, double _baths, string& _state)
{
    id = _id;
    url = _url;
    monthlyRent = _monthlyRent;
    type = _type;
    sqfeet = _sqfeet;
    beds = _beds;
    baths = _baths;
    state = _state;
}

// Prints all 8 attributes of a Listing in a neat format
void Listing::print()
{
    string stateUppercase = state;
    for (int i = 0; i < stateUppercase.length(); i++)
        stateUppercase[i] = (char)(stateUppercase[i] - 32);

    cout << "Listing ID: " << id << endl;
    cout << "Listing URL: " << url << endl;
    cout << "Monthly Rent: $" << monthlyRent << endl;
    cout << "Listing Type: " << type << endl;
    cout << "Square Feet: " << sqfeet << endl;
    cout << "Number of Bedrooms: " << beds << endl;
    cout << "Number of Bathrooms: " << baths << endl;
    cout << "State: " << stateUppercase << endl;
    cout << endl;
}
