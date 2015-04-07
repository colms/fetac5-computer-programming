#include <stdbool.h>

int main() {
  int user_input = 0; // input taken from user
  int primes[25]; // list of primes less than 100
  int possiblePrime; // number tested for primeness
  int divisor; // number that tries to evenly divde possiblePrime
  int primesFound = 1; // because we're hard coding 2 as prime
  bool isPrime; // indicates if the tested numer is prime
  bool valid_index = false; // indicates if user has entered a valid prime index

  // calculate primes
  primes[0] = 2;
  for (possiblePrime = 3; possiblePrime < 100; possiblePrime += 2) {
    isPrime = true; // assume it's true
    for (divisor = 3; divisor < possiblePrime / 2; divisor += 2) {
      if (possiblePrime % divisor == 0) {
          isPrime = false;
          break;
      }
    }
    if (isPrime == true) {
      primes[primesFound] = possiblePrime;
      ++primesFound;
    }
  }

  // loop forever
  while (true) {
    system("cls");
    printf("-1. Exit the program.\n");
    printf("1. Display primes less than 100.\n");
    printf("2. Enter index of prime less than 100 to be displayed.\n");
    scanf("%d", &user_input);
    if (user_input == -1) {
      return 0;
    } else if (user_input == 1) {
      // display primes
      int i;
      printf("primes:\n");
      for (i = 0; i < 25; ++i) {
        printf("%d\t", primes[i]);
      }
    } else if (user_input == 2) {
      printf("Enter the index of the prime you want to see: ");
      scanf("%d", &user_input);
      valid_index = true; // assume it's valid
      if (user_input < 1 || user_input > 25) {
        valid_index = false;
      }
      if (valid_index == true) {
        int selected_prime = primes[user_input - 1];
        printf("Prime value at index %d: %d\n", user_input, selected_prime);
      } else {
        printf("You must enter an index from 1 to 25\n");
      }
    }
    system("pause");
  }

  return 0;
}
