#ifndef SORT_TEST
#define SORT_TEST

#include "pipeline_data.h"

void test(pipeline_data& data);
bool integrity_test(int *unsorted, int *sorted, unsigned int len);
bool sort_test(int *arr, unsigned int len);

#endif