#ifndef __KV_H__
#define __KV_H__

// Structure to represent a single key/value pair
struct _kvpair_t { 
  char *key;   // Pointer to the key string
  char *value; // Pointer to the value string
};
typedef struct _kvpair_t kvpair_t;

// Structure to represent an array of key/value pairs
struct _kvarray_t { 
  kvpair_t *pairs; // Pointer to an array of key/value pairs
  size_t length;   // Number of key/value pairs in the array
};
typedef struct _kvarray_t kvarray_t;

// Function to read key/value pairs from a file
kvarray_t * readKVs(const char * fname);

// Function to free the memory allocated for key/value pairs
void freeKVs(kvarray_t * pairs);

// Function to print all key/value pairs
void printKVs(kvarray_t * pairs);

// Function to look up the value for a given key
char * lookupValue(kvarray_t * pairs, const char * key);

#endif
