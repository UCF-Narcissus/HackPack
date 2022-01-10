//Generating all subsets from a set of size n
//Subsets are stored by an inclusion array
void subsets(int i, int n, bool inc[]){
    //If index is at end of array, test the generated subset
    if(i == n){
        //test subset
        return;
    }
    //test subset where ith element isn't included
    inc[i] = false;
    subsets(i+1, n, inc);
    //test subset where ith elements is included
    inc[i] = true;
    subsets(i+1, n, inc);
}

//Generating all combinations of size m from a set of size n
void combine(int i, int j, int n, int m, int set[], int combo[]){
    //prune cases where there are not enough elements to finish the combination
    if(n-i < m-j)
        return;
    //if the combination is at full size, test it
    if(j == m){
        //test combination;
        return;
    }
    //combination not including ith element
    combine(i+1, j, n, m, set, combo);

    //combination not including ith element
    combo[j] = set[i];
    combine(i+1, j+1, n, m, set, combo);
}

//Generating all permutations of size m from a set of size n
void permute(int i, int n, int m, int set[], int perm[], bool used[]){
    //if the permutation is at full size, test it
    if(i == m){
        //test permutation
        return;
    }
    //loop through each element in the set
    for(int j = 0; j < n; j++){
        //if the element has not been used yet
        if(!used[j]){
            //set it to used
            used[j] = true;
            //add jth item to permutation
            perm[i] = set[j];
            //move onto next element
            permute(i+1, n, m, set, perm, used);
            //return jth item to unused to test other permutations
            used[j] = false;
        }
    }
}