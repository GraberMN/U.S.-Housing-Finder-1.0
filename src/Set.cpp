#include "Set.h"

Set::Node::Node(Listing& listing){
    data = listing;
    next = nullptr;
}

unsigned long long Set::hashFunc(string& id){
    unsigned long long hashCode = 0;
    for (size_t i = 0; i < id.length(); i++){
        hashCode = hashCode * 31 + (unsigned long long)(unsigned char)(id[i]);
    }
    return hashCode;
}

int Set::reduce(unsigned long long hashCode){
    return (int)(hashCode % numBuckets);
}

void Set::resize(){
    int oldNumBuckets = numBuckets;
    Node** oldBuckets = buckets;

    numBuckets *= 2;
    buckets = new Node*[numBuckets];
    for (int i = 0; i < numBuckets; i++){
        buckets[i] = nullptr;
    }

    for (int j = 0; j < oldNumBuckets; j++){
        Node* current = oldBuckets[j];
        while (current != nullptr){
            Node* nextNode = current->next;
            int index = reduce(hashFunc(current->data.id));
            current->next = buckets[index];
            buckets[index] = current;
            current = nextNode;
        }
    }
    loadFactor = (double)(numEntries) / (double)(numBuckets);
    delete[] oldBuckets;
}

void Set::searchTable(const function<bool(Listing&)>& matches, int& numFound){
    for (int i = 0; i < numBuckets; i++){
        Node* current = buckets[i];
        while (current != nullptr){
            if (matches(current->data)){
                current->data.print();
                numFound++;
            }
            current = current->next;
        }
    }
}

Set::Set(){
    numBuckets = 5;
    buckets = new Node*[numBuckets];
    for (int i = 0; i < numBuckets; i++){
        buckets[i] = nullptr;
    }
    numEntries = 0;
    loadFactor = (double)(numEntries) / (double)(numBuckets);
}

Set::~Set(){
    for (int i = 0; i < numBuckets; i++){
        Node* current = buckets[i];
        while (current != nullptr){
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    delete[] buckets;
}

void Set::insert(Listing& listing){
    int index = reduce(hashFunc(listing.id));

    Node* current = buckets[index];
    while (current != nullptr){
        if (current->data.id == listing.id){
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node(listing);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    numEntries++;
    loadFactor = (double)(numEntries) / (double)(numBuckets);

    if (loadFactor >= maxLoadFactor){
        resize();
    }
}

void Set::readInData(){
    auto time1 = chrono::high_resolution_clock::now();

    ifstream inFS;
    inFS.open("../data/housing.csv");
    if (!inFS.is_open()){
        cout << "Failed to open file." << endl;
        return;
    }
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
    while (getline(inFS, line)){
        istringstream inSS(line);
        getline(inSS, id, ',');
        getline(inSS, url, ',');
        getline(inSS, token, ',');
        try{
            monthlyRent = stoi(token);
        }
        catch (...){
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
    cout << numEntries << " listings read into the Set." << endl;

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::searchByMonthlyRent(int monthlyRentLower, int monthlyRentUpper){
    auto time1 = chrono::high_resolution_clock::now();

    cout << "Listings between $" << monthlyRentLower << " and $" << monthlyRentUpper << " (inclusive):" << endl;
    cout << endl;
    int numFound = 0;
    searchTable([&](Listing& listing){
        return listing.monthlyRent >= monthlyRentLower && listing.monthlyRent <= monthlyRentUpper;
    }, numFound);
    if (numFound == 1){
        cout << numFound << " listing found." << endl;
    }
    else{
        cout << numFound << " listings found." << endl;
    }

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::searchByType(string& type){
    auto time1 = chrono::high_resolution_clock::now();

    cout << "Listings of the " << type << " type:" << endl;
    cout << endl;
    int numFound = 0;
    searchTable([&](Listing& listing){
        return listing.type == type;
    }, numFound);
    if (numFound == 1){
        cout << numFound << " listing found." << endl;
    }
    else{
        cout << numFound << " listings found." << endl;
    }

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::searchBySqFeet(int sqfeetLower, int sqfeetUpper){
    auto time1 = chrono::high_resolution_clock::now();

    cout << "Listings between " << sqfeetLower << " and " << sqfeetUpper << " sqfeet (inclusive):" << endl;
    cout << endl;
    int numFound = 0;
    searchTable([&](Listing& listing){
        return listing.sqfeet >= sqfeetLower && listing.sqfeet <= sqfeetUpper;
    }, numFound);
    if (numFound == 1){
        cout << numFound << " listing found." << endl;
    }
    else{
        cout << numFound << " listings found." << endl;
    }

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::searchByNumBeds(int beds){
    auto time1 = chrono::high_resolution_clock::now();

    if (beds == 1){
        cout << "Listings with " << beds << " bedroom:" << endl;
    }
    else{
        cout << "Listings with " << beds << " bedrooms:" << endl;
    }
    cout << endl;
    int numFound = 0;
    searchTable([&](Listing& listing){
        return listing.beds == beds;
    }, numFound);
    if (numFound == 1){
        cout << numFound << " listing found." << endl;
    }
    else{
        cout << numFound << " listings found." << endl;
    }

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::searchByNumBaths(double baths){
    auto time1 = chrono::high_resolution_clock::now();

    if (baths == 1){
        cout << "Listings with " << baths << " bathroom:" << endl;
    }
    else{
        cout << "Listings with " << baths << " bathrooms:" << endl;
    }
    cout << endl;
    int numFound = 0;
    searchTable([&](Listing& listing){
        return listing.baths == baths;
    }, numFound);
    if (numFound == 1){
        cout << numFound << " listing found." << endl;
    }
    else{
        cout << numFound << " listings found." << endl;
    }

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::searchByState(string& state){
    auto time1 = chrono::high_resolution_clock::now();

    string stateUppercase = state;
    for (size_t i = 0; i < stateUppercase.length(); i++){
        stateUppercase[i] = (char)(stateUppercase[i] - 32);
    }
    cout << "Listings in the state of " << stateUppercase << ":" << endl;
    cout << endl;
    int numFound = 0;
    searchTable([&](Listing& listing){
        return listing.state == state;
    }, numFound);
    if (numFound == 1){
        cout << numFound << " listing found." << endl;
    }
    else{
        cout << numFound << " listings found." << endl;
    }

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}

void Set::printAll(){
    auto time1 = chrono::high_resolution_clock::now();

    cout << "All listings:" << endl;
    cout << endl;
    int numPrinted = 0;
    searchTable([](Listing&){
        return true;
    }, numPrinted);
    cout << numPrinted << " listings printed." << endl;

    auto time2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(time2 - time1);
    cout << "This operation took " << duration.count() << " milliseconds." << endl;
    cout << endl;
}