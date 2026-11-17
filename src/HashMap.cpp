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
    loadFactor = (double)(numEntries) / (double)(numBuckets);
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
        hashTable[index].first = listing.id;

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

