# apriori_algorithm_frequent_Itemset
Utilized Apriori Algorithm in Data mining to discover frequent-Itemsets in transactional databases
## To run the program, type the following command:
1. g++ apriori.cpp -o test
2. ./test

## Pseudo code for the algorithm:
1. Step 1: Finding frequent 1-itemset(L1) and k-itemset

Initialize a map to count the support of 1-itemset
For each item in transaction
    Increment each item

Initialize a vector to store frequent 1-itemset(L1)

Initialize a map to store support and count frequent k-itemset Lk

For each item in support count
    Check if item >= minimal support
        Add item to L1

Initialize a map to store support and count frequent k-itemset Lk


2. Step 2: Generate candidate itemset (Ck) by self-joining Lk-1 
            Eg: L3 = {abc, abd, ace, bcd}
                Self-Join: L3*L3 where abcd from abc and abd, acde from acd and ace
                Prunning: acde is removed because ade is not in L3
                Therefore, C4={abcd}

Initialize a vector to store candidate k-itemset(Lk)
Calculate k at current itemset
While Lk-1 is not empty:
    Initialize an empty list Lk
    For each itemset in (Lk-1) - 1
        For each itemset in (Lk-1)
            join itemset1 and itemset2
            check if join itemset has k element
            add it into Lk

3. Prunning Ck by checking (k-1)-subset

Initialize vector to store frequent k-itemset(Lk)
For each candidate in Ck
    isFrequent = True
    For each item in candidate
        Generate (k-1)-subset by removing item from candidate
        If subset not in Lk-1
            isFrequent = False
            break
    If isFrequent
        add candidate to Ck
