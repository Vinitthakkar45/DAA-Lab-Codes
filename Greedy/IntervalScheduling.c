#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int compare(const void* a, const void* b) {
    Interval* interval1 = (Interval*)a;
    Interval* interval2 = (Interval*)b;
    return interval1->end - interval2->end;
}

int maxNonOverlappingIntervals(Interval intervals[], int n) {

    // Sort intervals based on their end time
    qsort(intervals, n, sizeof(Interval), compare);

    // Following is the declaration for qsort() function.
    // void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))

    // Parameters
    //     base − This is the pointer to the first element of the array to be sorted.
    //     nitems − This is the number of elements in the array pointed by base.
    //     size − This is the size in bytes of each element in the array.
    //     compar − This is the function that compares two elements.



    int count = 1;
    int prev_end = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start >= prev_end) {
            count++;
            prev_end = intervals[i].end;
        }
    }
    return count;
}

int main() {
    int n;
    printf("Enter the number of intervals: ");
    scanf("%d", &n);

    Interval* intervals = (Interval*)malloc(n * sizeof(Interval));

    printf("Enter the intervals (start and end times):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    int maxNonOverlap = maxNonOverlappingIntervals(intervals, n);

    printf("Maximum number of non-overlapping intervals: %d\n", maxNonOverlap);

    free(intervals);

    return 0;
}
