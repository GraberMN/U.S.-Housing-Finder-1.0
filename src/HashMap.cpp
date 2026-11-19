//
// Created by grabe on 11/12/2026.
//

#include "HashMap.h"

// Hash function: return powers of 11 with ASCII
long long HashMap::hashFunc(string& id)
{
    long long hashCode = 0;
    for (int i = id.length() - 1; i >= 0; i--)
    {
        long long product = (int)(id[i]);
        for (int j = 0; j < (id.length() - 1) - i; j++)
            product *= 11;
        hashCode += product;
    }
    return hashCode;
}

// Reduces hashCode to index of hashTable
int HashMap::reduce(long long hashCode)
{
    return (int)(hashCode % numBuckets);
}

// Resizes hashTable when loadFactor >= maxLoadFactor by doubling its size and rehashing values
void HashMap::resize()
{
    numBuckets *= 2;
    pair<string, Listing>* tempHashTable = hashTable;
    hashTable = new pair<string, Listing>[numBuckets];
    for (int i = 0; i < numBuckets; i++)
        hashTable[i] = make_pair("", Listing());
    numEntries = 0;
    for (int j = 0; j < (numBuckets / 2); j++)
    {
        if (tempHashTable[j].first != "")
            insert(tempHashTable[j].second);
    }
    delete[] tempHashTable;
}

// Determines first open index in hashTable for insertion when a collision occurs
int HashMap::linearProbing(int index)
{
    while (hashTable[index].first != "")
        index = (index + 1) % numBuckets;
    return index;
}

// HashMap default constructor
HashMap::HashMap()
{
    numBuckets = 5;
    hashTable = new pair<string, Listing>[numBuckets];
    for (int i = 0; i < numBuckets; i++)
        hashTable[i] = make_pair("", Listing());
    numEntries = 0;
    loadFactor = (double)(numEntries) / (double)(numBuckets);
}

// HashMap destructor
HashMap::~HashMap()
{
    delete[] hashTable;
}

// Inserts a key value pair into the HashMap
void HashMap::insert(Listing& listing)
{
    numEntries++;
    loadFactor = (double)(numEntries) / (double)(numBuckets);
    int index = reduce(hashFunc(listing.id));

    // If no collision at index, insert there; otherwise, linear probe, then insert at firstOpenIndex
    if (hashTable[index].first == "")
    {
        hashTable[index].first = listing.id;

        hashTable[index].second.id = listing.id;
        hashTable[index].second.url = listing.url;
        hashTable[index].second.monthlyRent = listing.monthlyRent;
        hashTable[index].second.type = listing.type;
        hashTable[index].second.sqfeet = listing.sqfeet;
        hashTable[index].second.beds = listing.beds;
        hashTable[index].second.baths = listing.baths;
        hashTable[index].second.state = listing.state;
    }
    else
    {
        int firstOpenIndex = linearProbing(index);
        hashTable[firstOpenIndex].first = listing.id;

        hashTable[firstOpenIndex].second.id = listing.id;
        hashTable[firstOpenIndex].second.url = listing.url;
        hashTable[firstOpenIndex].second.monthlyRent = listing.monthlyRent;
        hashTable[firstOpenIndex].second.type = listing.type;
        hashTable[firstOpenIndex].second.sqfeet = listing.sqfeet;
        hashTable[firstOpenIndex].second.beds = listing.beds;
        hashTable[firstOpenIndex].second.baths = listing.baths;
        hashTable[firstOpenIndex].second.state = listing.state;
    }

    // Resizes hashTable if maxLoadFactor is reached or exceeded
    if (loadFactor >= maxLoadFactor)
        resize();
}

// Reads in all 380,000+ listings from dataset into the HashMap
void HashMap::readInData()
{
    auto time1 = chrono::high_resolution_clock::now();

    ifstream inFS;
    inFS.open("../data/housing.csv");
    if (!inFS.is_open())
        cout << "Failed to open file." << endl;
    string token;
    string line;
    getline(inFS, line);

    string id;
    string url;
    int monthlyRent;
    string type;
    int sqfeet;
    int beds;
    double baths;
    string state;
    while (getline(inFS, line))
    {
        istringstream inSS(line);
        getline(inSS, id, ',');
        getline(inSS, url, ',');
        getline(inSS, token, ',');
        try
        {
            monthlyRent = stoi(token);
        }
        catch (...)
        {
            // Deals with abnormally high monthly rents
            monthlyRent = INT_MAX;
        }
        getline(inSS, type, ',');
        getline(inSS, token, ',');
        sqfeet = stoi(token);
        getline(inSS, token, ',');
        beds = stoi(token);
        getline(inSS, token, ',');
        baths = stod(token);
        getline(inSS, state, ',');
        Listing listing(id, url, monthlyRent, type, sqfeet, beds, baths, state);
        insert(listing);
    }
    cout << numEntries << " listings read into the HashMap." << endl;

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

// Finds and prints out only the Listings within a given monthly rent range (inclusive)
void HashMap::searchByMonthlyRent(int monthlyRentLower, int monthlyRentUpper)
{
    auto time1 = chrono::high_resolution_clock::now();

    cout << "Listings between $" << monthlyRentLower << " and $" << monthlyRentUpper << " (inclusive):" << endl;
    cout << endl;
    int numFound = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        if (hashTable[i].first == "")
            continue;
        if (hashTable[i].second.monthlyRent >= monthlyRentLower && hashTable[i].second.monthlyRent <= monthlyRentUpper)
        {
            hashTable[i].second.print();
            numFound++;
        }
    }
    if (numFound == 1)
        cout << numFound << " listing found." << endl;
    else
        cout << numFound << " listings found." << endl;

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

// Finds and prints out only the Listings of a given housing type
void HashMap::searchByType(string& type)
{
    auto time1 = chrono::high_resolution_clock::now();

    cout << "Listings of the " << type << " type:" << endl;
    cout << endl;
    int numFound = 0;
    for (int i = 0; i < numBuckets; i++)
    {
        if (hashTable[i].first == "")
            continue;
        if (hashTable[i].second.type == type)
        {
            hashTable[i].second.print();
            numFound++;
        }
    }
    if (numFound == 1)
        cout << numFound << " listing found." << endl;
    else
        cout << numFound << " listings found." << endl;

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}
