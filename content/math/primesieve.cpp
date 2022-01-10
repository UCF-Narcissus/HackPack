//Description: Generate primes through n using the Sieve of Eratosthenes
void getPrimes(int n, bool isPrime[]){
    //set all indices to true
    memset(isPrime, true, sizeof(isPrime));
    //0 and 1 are not prime
    isPrime[0] = false;
    isPrime[1] = false;
    //loop from 2 to sqrt of max
    for(int i = 2; i < sqrt(n+1); i++){
        //if we find a prime
        if(isPrime[i]){
            //set each multiple of that prime to false;
            for(int j = i*2; j < n+1; j += i)
                isPrime[j] = false;
        }      
    }
}