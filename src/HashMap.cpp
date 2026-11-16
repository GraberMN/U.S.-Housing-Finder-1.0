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
