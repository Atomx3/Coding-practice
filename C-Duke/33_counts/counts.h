#ifndef __COUNTS_H__
#define __COUNTS_H__
// ../34_put_together, symbolink to ../33_counts/
// Structure to hold the count for a single name
struct _one_count_t {
  char * name;  // The name being counted
  int count;    // The number of times this name has been counted
};
typedef struct _one_count_t one_count_t;

// Structure to hold all counts
struct _counts_t {
  one_count_t * counts;  // Array of one_count_t structures
  size_t size;           // Number of elements in the counts array
  size_t unknown_count;  // Count of unknown (NULL) names
};
typedef struct _counts_t counts_t;

// Function prototypes
counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);
void freeCounts(counts_t * c);

#endif
