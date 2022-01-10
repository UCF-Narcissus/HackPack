// Description: Below are two algorithms. The first returns the greatest
//              common divisor and the second the least common multiple.

//Euclid's Algorithm
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }

//lcm = ab/gcd(a,b)
int lcm(int a, int b) { return a*b/gcd(a, b); }