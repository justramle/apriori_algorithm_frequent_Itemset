#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
//global value
vector<set<string>> transactions(20);

// Read the dataset from the input file and store it in a vector
vector<set<string>> readData(const string& filename) {
    vector<set<string>> transactions;
    ifstream input(filename);
    string line;

    while (getline(input, line)) {
        istringstream iss(line);
        string item;
        set<string> transaction;
        while (iss >> item) {
            transaction.insert(item);
        }
        transactions.push_back(transaction);
    }
    return transactions;
}

// function to write frequent itemset to output file
void writeFrequentItemsets(const string& filename, const vector<set<string>>& itemsets, const map<set<string>, int>& supportCounts,  int minSupport) {
    ofstream output(filename);

    // compare frequent k-itemsets with the minimum support
    vector<set<string>> frequentKItemsets;

    // Title
    int minPercent = (minSupport * 100)/transactions.size();
    output << "Minimal Support: " << minPercent << "%" << endl;

    for (const auto& value : supportCounts) {
        const set<string>& itemset = value.first;
        int support = value.second;

        if (support >= minSupport) {
            frequentKItemsets.push_back(itemset);
        }
    }
    // Print frequent itemsets along with their support counts
    for (const auto& itemset : frequentKItemsets) {
        output << "Itemset: {";
        for (const string& item : itemset) {
            output << item << " ";
        }
        output << "}\t| Support Count : " << supportCounts.at(itemset) << endl;
    }
}

//function to calculate the support count for an itemset in transactions
int supportCount(const set<string>& itemset, const vector<set<string>>& transactions) {
    int count = 0;
    for (const set<string>& transaction : transactions) {
        if (includes(transaction.begin(), transaction.end(), itemset.begin(), itemset.end())) {
            count++;
        }
    }
    return count;
}

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";

    vector<set<string>> transactions = readData(inputFile);
    vector<set<string>> L1; // Frequent 1-itemset

    // Set the minimum support to 50% of the total transactions
    // 10% 20% 30% 50%
    // testing with 60% - 80%. Only sucessful on large minSupport
    int minSupport = transactions.size() * 0.6; 

    // count frequent 1-itemsets
    map<string, int> itemSupportCount;
    for (const set<string>& transaction : transactions) {
        for (const string& item : transaction) {
            itemSupportCount[item]++;
        }
    }

     // compare frequent 1-itemsets with the minimum support
    for (const auto& entry : itemSupportCount) {
        if (entry.second >= minSupport) {
            // Maintain L1 with frequent 1-itemsets
            L1.push_back({entry.first});
        }
    }

    // Store support counts for frequent itemsets
    // Initilize L1 compare SupCount with minSup 
    vector<set<string>> frequentItemsets = L1;

    // Start with 2-itemsets
    int k = 2; 
    while (!L1.empty()) {
        // Self-join Lk-1 to generate Ck
        vector<set<string>> Ck;
        //join itemset at current step
         k = L1[0].size() + 1;

        for (size_t i = 0; i < L1.size(); i++) {
            for (size_t j = i + 1; j < L1.size(); j++) {
                set<string> itemset1 = L1[i];
                set<string> itemset2 = L1[j];

                // Join two itemsets by combining the first (k-2) elements
                set<string> joinedItemset = itemset1;
                for (const string& item : itemset2) {
                    if (itemset1.find(item) == itemset1.end()) {
                        joinedItemset.insert(item);
                    }
                }

                // Check if the joined itemset has k elements
                if (joinedItemset.size() == k) {
                    Ck.push_back(joinedItemset);
                }
            }
        }

        // Prune Ck by checking its (k-1)-subsets
        vector<set<string>> Lk = Ck;
        for (const set<string>& candidate : Ck) {
            bool isFrequent = true;
            for (const string& item : candidate) {
                set<string> subset = candidate;
                subset.erase(item);

                if (find(L1.begin(), L1.end(), subset) == L1.end()) {
                    isFrequent = false;
                    break;
                }
            }
            if (isFrequent){
                Lk.push_back(candidate);
            }
        }
        if (!Lk.empty()) {
            frequentItemsets.insert(frequentItemsets.end(), Lk.begin(), Lk.end());
        }
        L1 = Lk;
        k++;
    }

    //Calculate the support counts for frequent k-itemsets
    map<set<string>, int> supportCounts;
    for (const set<string>& itemset : frequentItemsets) {
        int support = supportCount(itemset, transactions);
        supportCounts[itemset] = support;
    }
    
    // Write frequent itemsets to the output file
    writeFrequentItemsets(outputFile, frequentItemsets, supportCounts, minSupport);

    return 0;
}
