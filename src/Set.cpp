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
    loadFactor = (double)(numEntries)/ (double)(numBuckets);
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

