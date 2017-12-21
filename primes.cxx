#include <iostream>
using namespace std;
#include <vector>

/*
 * Class to generate prime numbers.
 * Includes variables primes_found and last_prime to keep track of 
 * how many primes were found and the last generated one, as well as
 * functions last_prime_found, number_of_primes_found, next_prime and is_prime(int x).
 */
class primegenerator {
    private:
        int primes_found = 0;
        int last_prime = 1;
    public:
        int last_prime_found() {
            return last_prime;
        }
        int number_of_primes_found() {
            return primes_found;
        }
        int next_prime() {
            last_prime++;
            while (!is_prime(last_prime)) {
                last_prime++;
            } 
            primes_found++;
            return last_prime;
        }
        bool is_prime(int x) {
            int divisors[x];
            int numdivisors = 0;

            // Check all smaller positive integers >= 2 for divisors
            for (int i = 2; i < x; i++) {
                if (x % i == 0) {   // Store divisors to list in final print message
                    divisors[numdivisors] = i; 
                    numdivisors++;
                    //cout << "Divisible by " << i << endl;
                } else {
                    //cout << "Not divisible by " << i << endl;
                }
            }

            if (numdivisors > 0) {
                //cout << "Your number is not prime. It is divisible by " << divisors[0] << "." << endl; 
                return false;
            } else {
                //cout << "Your number is prime!" << endl;
                return true;
            } 
        }
};

/*
 * Same as the is_prime function in the primegenerator class for general use.
 */
bool is_prime(int x) {
    int divisors[x];
    int numdivisors = 0;

    // Check all smaller positive integers >= 2 for divisors
    for (int i = 2; i < x; i++) {
        if (x % i == 0) {   // Store divisors to list in final print message
            divisors[numdivisors] = i; 
            numdivisors++;
        } 
    }

    if (numdivisors > 0) {
        //cout << "Your number is not prime. It is divisible by " << divisors[0] << "." << endl; 
        return false;
    } else {
        //cout << "Your number is prime!" << endl;
        return true;
    } 
}

/* 
 * Finds a prime q that fulfills the Goldbach Conjecture as per Exercise 38.11
 */
int find_q(int p) {
    primegenerator qgenerator;
    do {
        qgenerator.next_prime();
    } while (!is_prime(2 * p - qgenerator.last_prime_found()));
    return qgenerator.last_prime_found();
}

/* 
 * Finds primes in a range starting with 2 and ending with user input value, 
 * as per Exercise 38.8
 */
void eratosthenes_sieve(int end) {
    if (end < 2) {  // Check for valid range end value
        cout << "End of range must be >= 2." << endl;
        return;
    }

    // Initialize vector with consecutive integers from 2 to end, inclusive
    vector<int> sieve(end - 1, 2);
    int count = 0;
    for (auto &e : sieve) {
        e += count;
        count++;  
    }

    // Repeat steps of reporting and scratching out multiples until all reported
    unsigned index = 0;
    int current;
    while (sieve.size() > 0) {
        current = sieve.at(0);  // Get first element
        cout << "Next prime: " << current << endl;  // Report it

        while (index < sieve.size()) {  // Scratch out all other multiples
            if (sieve.at(index) % current == 0) {
                sieve.erase(sieve.begin() + index);
            } else {
                index++;
            } 
        }
        index = 0;
    }
}

/* 
 * Main program asks for user specified range ends or number of primes to print for each Chapter
 * 38 exercise.
 */
int main() {
    // Exercise 38.9, ask user for number of primes to print starting from 2
    int how_many;
    cout << "Exercise 38.9, printing primes using a class: How many primes to print? " << endl;
    cin >> how_many;

    primegenerator sequence;
    while (sequence.number_of_primes_found() < how_many) {
        int num = sequence.next_prime();
        cout << sequence.number_of_primes_found() << ": " << num << " is prime." << endl;
    } 


    // Exercise 38.10, find primes p and q for even even number e up to 20 million such that n = p + q
    cout << "Exercise 38.10, finding p and q s.t n = p + q for even n up to what number?" << endl;
    do {    // Make sure input is valid
        cout << "Need an even number > 2." << endl;
        cin >> how_many;
    } while (how_many % 2 != 0 || how_many <= 2);

    // Double loop to test each e - p to see if it's prime, stopping once one is found
    for (int even = 2;  even < how_many; even +=2) {
        primegenerator primetester;
        while (primetester.next_prime() < even) {
            if (is_prime(even - primetester.last_prime_found())) {
                cout << even << " = " << primetester.last_prime_found() << " + " << even - primetester.last_prime_found() << endl; 
                break;
            }
        }
    }

    // Exercise 38.11, find prime q for each prime p s.t. p + (p - q) is prime
    cout << "Exercise 38.11: Goldbach Conjecture proving that for every prime p, r = p + (p - q) is prime for some prime q. How many primes to test?" << endl;
    cin >> how_many;
    int distances[how_many];

    // Test each prime found by pgenerator
    primegenerator pgenerator;
    int p = 0, q = 0, count = 0;
    while(pgenerator.number_of_primes_found() < how_many) {
        p = pgenerator.next_prime();    // Get next p prime
        q = find_q(p);  // find_q creates a q generator to find a suitable q value
        distances[count] = p - q;   // Record distance 
        count++; 

        //Report p, q, r triple
        cout << "p = " << p << " q = " << q << " r = " << 2*p - q << endl;
    }

    // Print all distances and average distance
    float sum = 0;
    for (int i = 0; i < how_many; i++) {
        cout << "Distance " << i << ": " << distances[i] << endl;
        sum += distances[i];
    }
    cout << "Average distance: " << sum / how_many << endl;

    // Exercise 38.8: finding range of prime numbers using the eratosthenes sieve algorithm in a vector
    cout << "Exercise 38.8: Using eratosthenes sieve: where to end range of numbers to test? " << endl;
    cin >> how_many;
    eratosthenes_sieve(how_many);

    return 0;
}
