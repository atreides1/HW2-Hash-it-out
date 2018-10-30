# HW2-Hash-it-out
Sierra and Mercy's Cache homework assignment for CSCI 389 (If possible, view on your favorite text editor - Github's README format is messy.)

Important Files: 
cache.hh - Unmodified header file used to guide cache implementation
cache.cc - Creates a cache using an unordered map of key/value pairs, then an ordered map of key/size pairs.
Since storage and access is delegated to the unordered map, it allowed us to include functionality that utilized 
umap's included properites:
  umap uses its own hash function, but also allows you to set your own, if included in the parameters during initialization.
    For our purposes, we implemented this using a lambda function.
  umap uses buckets when hashing, which allows us to avoid collisions.
  max_load_factor() allows us to set the load factor of our umap, allowing for dynamic resizing.
  count(key) allows us to see the number of items for a given hashed bucket in umap, so we can tell if there's a value (i.e. a specific key) is stored within the umap.
  
The eviction policy uses FIFO. The key/val pairs are stored in umap, and the key/index_sizes are stored in a regular map. Since the regular map is in 
order, our evictor_FIFO() finds the first key in the key_bytes map, then deletes the stored values in key_bytes AND storage using that key.

test.cc - Creates a set of functions that test behavior on the edge such as deleting nonexistant keys, general querying, 
and querying for a key that wasn't inserted. The test functions are then called in main.

Note: To compile, use "g++-7 -Wall -Wextra -pedantic cache.cc test.cc -o test"

Output from compiled test.cc:
```
TEST: Create cache and insert key:
Inserting: Key: a, Value: 0x7ffdc2fa5786

TEST: Query key:
Inserting: Key: a, Value: 0x7ffdc2fa5786
Retrieving: Key: a, Value: 0x7ffdc2fa5786

TEST: Query key that wasn't inserted:
Inserting: Key: a, Value: 0x7ffdc2fa5786
Key: b not found.

TEST: Insert key and modify value:
Inserting: Key: a, Value: 0x7ffdc2fa5784
Original value: Retrieving: Key: a, Value: 0x7ffdc2fa5784
Inserting: Key: a, Value: 0x7ffdc2fa5786
New value: Retrieving: Key: a, Value: 0x7ffdc2fa5786

TEST: Create cache and delete key:
Inserting: Key: a, Value: 0x7ffdc2fa5786
deleting... Retrieving: Key: a, Value: 0x7ffdc2fa5786
Key: a successfully deleted.

TEST: Create cache and check for deleted value:
Inserting: Key: a, Value: 0x7ffdc2fa5786
deleting... 
Retrieving: Key: a, Value: 0x7ffdc2fa5786
Key: a successfully deleted.
access deleted val: Key: a not found.

TEST: Create cache and delete an uninserted key:
deleting... Key not stored in cache.

TEST: FIFO Eviction:
The cache has a size of 5 bytes
Inserting: Key: a, Value: 0x7ffdc2fa5786
Inserting: Key: b, Value: 0x7ffdc2fa5786
Inserting: Key: c, Value: 0x7ffdc2fa5786
Inserting: Key: d, Value: 0x7ffdc2fa5786
Key: a successfully deleted.
Inserting: Key: e, Value: 0x7ffdc2fa5786
Attempting to retrieve evicted key 'a'...
Key: a not found.
```
