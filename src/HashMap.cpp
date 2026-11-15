//
// Created by grabe on 11/12/2026.
//

#include "HashMap.h"

HashMap::HashMap()
{
    numBuckets = 5;
    hashTable = new pair<string, Listing>[numBuckets];
    for (int i = 0; i < numBuckets; i++)
        hashTable[i] = make_pair("", Listing());
    numEntries = 0;
    loadFactor = (double)(numEntries) / (double)(numBuckets);
}

HashMap::~HashMap()
{
    delete[] hashTable;
}
