
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

void counting_sort(uint16_t * array, size_t array_l, uint16_t min, uint16_t max);
uint16_t * prompted(uint16_t * list, size_t * list_l);

/// MARK: report()
/// Display values in array
/// @param array target array
/// @param array_l array size
inline
static
void report(uint16_t * array, size_t array_l) {
  for(size_t i_ = 0, col = 0; i_ < array_l; i_++) {
    printf(" %04hX%s", array[i_], ((++col % 10) == 0) ? "\n" : ",");
  }
  putchar('\n');

  return;
}

/// MARK: main()
/// Program entry point
/// @param argc count of input arguments
/// @param argv array of input arguments
int main(int argc, const char * argv[]) {
  printf("AS_CountingSort\n");

  uint16_t * list = NULL;
  size_t list_l;
  list = prompted(list, &list_l);
  report(list, list_l);
  putchar('\n');
  counting_sort(list, list_l, 0x0000, 0xffff);
  report(list, list_l);
  putchar('\n');
  free(list);

  return EXIT_SUCCESS;
}

/// MARK: counting_sort_mm()
/// Counting sort implimenntation
/// @param array array of values to sort
/// @param array_l array length
/// @param min smallest value in array
/// @param max largest value in array
void counting_sort(uint16_t * array, size_t array_l, uint16_t min, uint16_t max) {
  size_t range = max - min + 1;
  uint8_t * count = calloc(range, sizeof(uint8_t));

  for (size_t i_ = 0; i_ < array_l; i_++) {
    count[ array[i_] - min ]++;
  }

  for (size_t i_ = min, z_ = 0; i_ <= max; i_++) {
    for (size_t j_ = 0; j_ < count[i_ - min]; j_++) {
      array[z_++] = (uint16_t) i_;
    }
  }

  free(count);
}

/// MARK: prompted
/// Collect input from user
/// @param list pointer for target array
/// @param list_l pointer for target array size
uint16_t * prompted(uint16_t * list, size_t * list_l) {
  printf("How many entries?: ");
  fflush(stdout);
  scanf("%zu", list_l);

  uint16_t val;
  list = calloc(*list_l, sizeof(uint16_t));
  //  Example input: 0x8946 0xF71 0xAEB 0xD98 0xECA
  printf("Enter %zu values: ", *list_l);
  fflush(stdout);
  for (size_t e_ = 0; e_ < *list_l; ++e_) {
    scanf("%hi", &val);
    list[e_] = val;
  }

  return list;
}
