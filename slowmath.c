//slowmath
// for when you have float but don't have trig
#include "slowmath.h"

// numerical constants
const float EPSILON = 0.00001; // the error tolerance for approximation methods
const int   LOG_ITTERS = 160;  // increasing this builds accuracy into LOG generation
const float NATURAL_LOG_OF_10 = 2.30258;


// This function returns the square root of a positive number using Newton's method
float smsquareRoot(float num) {
    float guess = num / 2; // Initial guess

    // Iterate until the guess is accurate enough
    while ((guess * guess > num ? guess * guess - num : num - guess * guess) > EPSILON) {
        guess = (guess + num / guess) / 2;
    }

    return guess;
}


// This function returns the sine of an angle in radians using the Taylor series expansion
float smsine(float rad) {

    float result = rad; // Initialize result with rad itself
    float term = rad; // Initialize the first term

    // Iterate to calculate more terms
    for (int i = 3; term != 0; i += 2) {
        term = term * (-rad * rad) / (i * (i - 1)); // Calculate the next term using the formula
        result += term; // Add the term to the result
    }

    return result;
}

// This function returns the cosine of an angle in radians using the Taylor series expansion
float smcosine(float rad) {

    float result = 1; // Initialize result with the first term
    float term = 1; // Initialize the first term

    // Iterate to calculate more terms
    for (int i = 2; term != 0; i += 2) {
        term = term * (-rad * rad) / (i * (i - 1)); // Calculate the next term using the formula
        result += term; // Add the term to the result
    }

    return result;
}

// This function returns the tangent of an angle in radians using the ratio of sine and cosine
float smtangent(float rad) {
    return smsine(rad) / smcosine(rad); // Use the previously defined functions
}

// This function returns the natural logarithm of a positive number using the Taylor series expansion

 float smlog(float num) {
    if (num <= 0) return -1;  //return -1 for non-positive number these do not exist in naturals.

    // the talior series returns a value with more precision when we add more terms -
    // going more than this makes a very slow equation significanty slower.
    // on the stock COCO / DRAGON this is VERY SLOW and LOG10 IS 2x as SLOW. AT 5Mhz E on the 6309
    // it is much faster.

    float result = 0;
    float term = (num - 1) / (num +1); // Calculate the first term using the formula
    float term_squared = term * term; // Store the square of the term for efficiency
    float numerator = term; // Initialize the numerator with the first term
    float denominator = 1; // Initialize the denominator with 1

    // Iterate to calculate more terms
    for (int i = 1 ; i <= LOG_ITTERS; i += 2) { // Adjust the iteration count for accuracy
        result += numerator / denominator; // Add the term to the result
        numerator *= term_squared; // Multiply the numerator by the square of the term
        denominator += 2; // Increment the denominator by 2

    }
    return 2 * result; // Multiply the result by 2 to get the final value

}

// This function returns the base 10 logarithm of a positive number using the natural logarithm and the change of base formula
 // Use the previously defined function and the formula log_a(b) = log_c(b) / log_c(a)
float smlog10(float num) {
    return smlog(num) / NATURAL_LOG_OF_10;
}
