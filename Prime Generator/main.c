#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*def getSophieGermainSafePrime(bits):
    inform(GETTING_SAFE_PRIME_INFO)

    while True:
        safe_prime = getPrimeNumber(bits)
        sophie_germain_prime = (safe_prime - 1) >> 1

        if passesMillerRabinTest(sophie_germain_prime):
            return safe_prime*/

/*def getPrimeNumber(bits):
    while True:
        prime_cadidate = getPrimeCandidate(bits)

        if passesMillerRabinTest(prime_cadidate):
            return prime_cadidate  */

       /*     def getPrimeCandidate(bits): 
    while True:  
        prime_candidate = getRandomOddNumber(bits)  

        for divisor in REFERENCE_PRIME_LIST:  
            if (prime_candidate % divisor == 0) and (divisor ** 2 <= prime_candidate): 
                break
            
            else: 
                return prime_candidate*/


/*def getRandomOddNumber(bits):
    real_bits = bits - 1
    bit_mask = (1 << 0) + (1 << real_bits) # Set the last bit to 1 so that the number is always the exact number of bits, and the first bit to 1 so the number is always odd.

    random_number = secrets.randbits(real_bits) | bit_mask

    return random_number*/

int bits2Integer(unsigned char array_of_bits[], unsigned int number_of_bits){
    unsigned int bit_mask = number_of_bits - 1;
    int result = 0;

    for(int i = 0; i < number_of_bits; i++)
        if(array_of_bits[i] == 1)
            result |= 1 << (bit_mask - i);

    return result;
}

unsigned int rand_bit() {
    unsigned int limit;
    unsigned int random_number;
    unsigned int upper_bound = 2;
   
    limit = RAND_MAX - (RAND_MAX % upper_bound);
   
    while((random_number = rand()) >= limit);
   
    return random_number % upper_bound;
}

unsigned int get_random_odd_number(unsigned int number_of_bits) {
    unsigned char bit_array[number_of_bits];
    int bit_mask;

    for (int i = 0; i < number_of_bits; i++) {
        bit_array[i] = rand_bit();
    }

    bit_array[0] = 1; // Set the first bit so it is always the bit size specified
    bit_array[number_of_bits - 1] = 1; // Set the last bit to make it odd

    printf("Num Bits: %d\n", number_of_bits);
    printf("Bits: ");

    for (int i = 0; i < number_of_bits; i++) {
        printf("%d", bit_array[i]);
    }

    printf("\n");

    int number = bits2Integer(bit_array, number_of_bits);
    printf("NUM: %u\n", number);

    return 0;

    //bit_mask = (1 << 0) + (1 << real_number_of_bits);
}

unsigned int get_prime_candidate() {
    //while (true) {
        /* code */
    //}

    unsigned int number_of_bits = 16;
    unsigned int prime_candidate;

    prime_candidate = get_prime_candidate(number_of_bits);
}

unsigned int get_prime_number() {
    //while (true) {
        /* code */
    //}

    unsigned int number_of_bits = 16;
    unsigned int prime_candidate;

    prime_candidate = get_prime_candidate(number_of_bits);
}

unsigned int get_safe_prime() {
    printf("Getting safe prime...\n");

    //while (true) {
        /* code */
    //}
    

    return 1;
}



int main() {
    unsigned int safe_prime;

    //safe_prime = get_safe_prime();
    unsigned int seed;
    FILE* urandom = fopen("/dev/urandom", "r");
    fread(&seed, sizeof(int), 1, urandom);
    fclose(urandom);
    srand(seed);

    /*unsigned int bit_array[16];

    printf("Bits: ");

    for (int i=0; i<16; i++) {
        bit_array[i] = rand_range(2);
        printf("%i", bit_array[i]);
    }*/


    unsigned int number_of_bits = 16;


    get_random_odd_number(number_of_bits);

    /*unsigned char bit_array[number_of_bits]; //"01010010111011";
    //101001011101100000000001
    //1010010111011
    //1010010111011
    //unsigned int bit_array_lenth = sizeof(bit_array) / sizeof(bit_array[0]);

    printf("Num Bits: %d\n", number_of_bits);
    printf("Bits: ");

    for (int i=0; i<number_of_bits; i++) {
        bit_array[i] = rand_range(2);
        printf("%d", bit_array[i]);
    }

    int coso = bits2Integer(bit_array, number_of_bits);
    printf("\n");
    printf("Bit array: %u\n", coso);*/

    return 0;
}