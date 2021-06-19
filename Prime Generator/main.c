#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include <unistd.h>

const int PRIME_DIVISORS_ARRAY_LENGHT = 46;
const unsigned long int PRIME_DIVISORS_ARRAY[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

char rand_bit() {
    int limit, result, random_number;
    int upper_bound = 2;
   
    limit = RAND_MAX - (RAND_MAX % upper_bound);
   
    while((random_number = rand()) >= limit);

    result = random_number % upper_bound;

    return result += '0'; // Make it a char
}

char * get_random_odd_number(unsigned int number_of_bits) {
    char *bit_array = malloc( number_of_bits * sizeof(char) ); 

    for (int i = 0; i < number_of_bits; i++) {
        bit_array[i] = rand_bit();
    }

    bit_array[0] = '1';                  // Set the first bit so it is always the bit size specified
    bit_array[number_of_bits - 1] = '1'; // Set the second to last bit to make it odd
    bit_array[number_of_bits] = '\0';    // Add null termination to make it a string

    //printf("Generated odd number: 0b%s\n", bit_array);

    return bit_array;
}

int passes_miller_rabin_test( mpz_t *candidate ) {
    int number_of_iterations = 40;
    int max_divisions_by_two = 0;

    bool is_probably_prime = true;

    mpz_t candidate_number;
    mpz_t candidate_minus_one;
    mpz_t even_component;
    mpz_t test_number;
    mpz_t test_number_limit;
    mpz_t first_pow_mod_result;
    mpz_t second_pow_mod_exponent;
    mpz_t second_pow_mod_result;
    
    gmp_randstate_t state;

    mpz_init_set( candidate_number, *candidate ); // Only way for candidate to not become zero

    mpz_init(candidate_minus_one);
    mpz_init(test_number);
    mpz_init(test_number_limit);
    mpz_init(first_pow_mod_result);
    mpz_init(second_pow_mod_result);
    mpz_init(second_pow_mod_exponent);

    mpz_sub_ui( candidate_minus_one, candidate_number, 1 );
    mpz_sub_ui( test_number_limit, candidate_number, 4 );
    
    mpz_init_set( even_component, candidate_minus_one );
    
    gmp_randinit_mt(state);

    gmp_printf("Testing %Zi      %s", candidate_number, "\x1b[1m[ TESTING ]\x1b[0m");

    while ( mpz_even_p(even_component) ){
        mpz_cdiv_q_ui( even_component, even_component, 2 );
        max_divisions_by_two += 1;
    }

    for (int i = 0; i <= number_of_iterations; i++) {
        mpz_urandomm( test_number, state, test_number_limit );
        mpz_add_ui( test_number, test_number, 2 );

        mpz_powm( first_pow_mod_result, test_number, even_component, candidate_number );

        if (mpz_cmp_ui(first_pow_mod_result, 1) == 0 || mpz_cmp(first_pow_mod_result, candidate_minus_one) == 0) {
            continue;
        }

        for (int j = 0; j < max_divisions_by_two; j++) { 
            mpz_mul_2exp( second_pow_mod_exponent, even_component, j );
            mpz_powm( second_pow_mod_result, test_number, second_pow_mod_exponent, candidate_number );

            if (mpz_cmp(second_pow_mod_result, candidate_minus_one) == 0) {
                is_probably_prime = true;

                i = number_of_iterations + 1; // exit for i loop to
                break;                        // Clear all gmp vars
            }
        }

        is_probably_prime = false;
    }

    if ( is_probably_prime ) {
        gmp_printf("\rTesting %Zi      %s", candidate_number, "\x1b[1;92m[ PASSED ]\x1b[0m \n");
        
    } else {
        gmp_printf("\rTesting %Zi      %s", candidate_number, "\x1b[1;91m[ FAILED ]\x1b[0m \n");

    }

    mpz_clear(candidate_number);
    mpz_clear(candidate_minus_one);
    mpz_clear(even_component);
    mpz_clear(test_number);
    mpz_clear(test_number_limit);
    mpz_clear(first_pow_mod_result);
    mpz_clear(second_pow_mod_exponent);
    mpz_clear(second_pow_mod_result);

    gmp_randclear(state);

    

    return is_probably_prime;
}


void get_prime_candidate(unsigned int number_of_bits, mpz_t prime_candidate_pointer) {
    char *prime_candidate_bits;
    unsigned long int divisor;

    mpz_t prime_candidate;
    mpz_t mod_result;
    mpz_t divisor_squared;




    mpz_init(prime_candidate);
    mpz_init(mod_result);
    mpz_init(divisor_squared);

    bool candidate_found = false;

    while ( !candidate_found ) {
        prime_candidate_bits = get_random_odd_number(number_of_bits);
        mpz_set_str( prime_candidate, prime_candidate_bits, 2 );

        for (int i = 0; i < PRIME_DIVISORS_ARRAY_LENGHT; i++) {
            divisor = PRIME_DIVISORS_ARRAY[i];

            mpz_mod_ui( mod_result, prime_candidate, divisor );
            mpz_ui_pow_ui( divisor_squared, divisor, 2 );

            if (mpz_cmp_ui( mod_result, 0 ) == 0 && mpz_cmp( divisor_squared, prime_candidate ) <= 0) { 
                candidate_found = false;
                break;
            }

            candidate_found = true;
        }
    }

    mpz_clear(mod_result);
    mpz_clear(divisor_squared);

    gmp_printf("CPRMIMEIME  BEFFFF %Zi\n", prime_candidate);

    prime_candidate_pointer = prime_candidate;
}

mpz_t * get_prime(unsigned int number_of_bits) {
    mpz_t prime_candidate;
    mpz_t *prime_candidate_pointer;
    
    prime_candidate_pointer = &prime_candidate;
    mpz_init(prime_candidate);

    printf("Generating a %u bit prime number\n\n", number_of_bits);
    printf("Checking primality with Miller-Rabin test\n");


    while (true) {
        get_prime_candidate(number_of_bits, prime_candidate);

        gmp_printf("CPRMIMEIME %Zi\n", prime_candidate);

        mpz_set(prime_candidate, *prime_candidate_pointer); // Backup value of prime candidate



        if ( passes_miller_rabin_test(prime_candidate_pointer) ) {
            prime_candidate_pointer = &prime_candidate;
            
            return prime_candidate_pointer;
        }

        
    }
}

void show_formatted_time(double time_spent) {
    char *si_unit = "s";
    
    if ( time_spent < 0.001 ) {
        si_unit = "µs";
        time_spent = time_spent * 1000000; 

    } else if ( time_spent < 1 ) {
        si_unit = "ms";
        time_spent =  time_spent * 1000;

    } else if ( time_spent > 60 ) {
        si_unit = "min";
        time_spent =  time_spent / 60; 
    }

    printf(", it took \x1b[1;93m%.0f%s\x1b[0m\n", time_spent, si_unit);
}

int main( int argc, char *argv[] ) {
    unsigned int seed;
    unsigned int number_of_bits;

    FILE* urandom = fopen("/dev/urandom", "r");
    fread( &seed, sizeof(int), 1, urandom );
    fclose(urandom);

    srand(seed);

    mpz_t *prime_pointer;

    clock_t begin, end;

    if ( argc < 2 ) { 
        printf("Please specify the number of bits\n");
        return 1;
    }

    number_of_bits = atoi(argv[1]);

    begin = clock();

    /* here, do your time-consuming job */
    prime_pointer = get_prime(number_of_bits);
    gmp_printf( "\nGenerated the prime number \x1b[1;97m%Zi\x1b[0m", *prime_pointer );

    end = clock();

    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

    show_formatted_time(time_spent);

    return 0;
}