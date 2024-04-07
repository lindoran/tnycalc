// gcc program for testing slowmath.h against math.h

#include <stdio.h>
#include <math.h>

#include "slowmath.h"

int main() {
  // test values in radians
  // loop through the test values
    float test_values[] = {0.5, 1, 1.5, 2, 2.5, 3}; // these must be radians as well..

    // print the test value
    for (int i = 0; i < 7; i++) {
    printf("TEST VALUE: %f\n", test_values[i]);
    // print the square root using slowmathand math.h
    printf("S.ROOT SM: %f\n", smsquareRoot(test_values[i]));
    printf("S.ROOT SL: %f\n", sqrt(test_values[i]));
    // print the sine using slowmathand math.h
    printf("SIN USING SM: %f\n", smsine(test_values[i]));
    printf("SIN USING SL: %f\n", sin(test_values[i]));
    // print the cosine using slowmathand math.h
    printf("COS USING SM: %f\n", smcosine(test_values[i]));
    printf("COS USING SL: %f\n", cos(test_values[i]));
    // print the tangent using slowmathand math.h
    printf("TAN USING SM: %f\n", smtangent(test_values[i]));
    printf("TAN USING SL: %f\n", tan(test_values[i]));
    // print the natural logarithm using slowmathand math.h
    printf("LOG USING SM: %f\n", smlog(test_values[i]));
    printf("LOG USING SL: %f\n", log(test_values[i]));
    // print the log10 test_values
    printf("LOG10 USING SM: %f\n", smlog10(test_values[i]));
    printf("LOG10 USING SL: %f\n", log10(test_values[i]));
    // print a new line
    printf("\n");
    }
  return 0;
}
