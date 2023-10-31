# apriori_algorithm_frequent_Itemset
Utilized Apriori Algorithm in Data mining to discover frequent-Itemsets in transactional databases
## To run the program, type the following command:
1. g++ apriori.cpp -o test
2. ./test

## Pseudo code for the algorithm:
1. Step 1: Finding frequent 1-itemset(L1) and k-itemset

Initialize a map to count the support of 1-itemset

For each item in transaction\
&nbsp;&nbsp;&nbsp;&nbsp;Increment each item

Initialize a vector to store frequent 1-itemset(L1)

Initialize a map to store support and count frequent k-itemset Lk

For each item in support count\
&nbsp;&nbsp;&nbsp;&nbsp;Check if item >= minimal support\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Add item to L1

Initialize a map to store support and count frequent k-itemset Lk


2. Step 2: Generate candidate itemset (Ck) by self-joining Lk-1
   
            Eg: L3 = {abc, abd, ace, bcd}
                Self-Join: L3*L3 where abcd from abc and abd, acde from acd and ace
                Prunning: acde is removed because ade is not in L3
                Therefore, C4={abcd}

Initialize a vector to store candidate k-itemset(Lk)\

Calculate k at current itemset

While Lk-1 is not empty:\
&nbsp;&nbsp;&nbsp;&nbsp;Initialize an empty list Lk\
&nbsp;&nbsp;&nbsp;&nbsp;For each itemset in (Lk-1) - 1\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;For each itemset in (Lk-1)\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;join itemset1 and itemset2\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;check if join itemset has k element\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;add it into Lk

3. Prunning Ck by checking (k-1)-subset

Initialize vector to store frequent k-itemset(Lk)\
For each candidate in Ck\
&nbsp;&nbsp;&nbsp;&nbsp;isFrequent = True\
&nbsp;&nbsp;&nbsp;&nbsp;For each item in candidate\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Generate (k-1)-subset by removing item from candidate\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;If subset not in Lk-1\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;isFrequent = False\
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;break\
&nbsp;&nbsp;&nbsp;&nbsp;If isFrequent\
&nbsp;&nbsp;&nbsp;&nbsp;add candidate to Ck
