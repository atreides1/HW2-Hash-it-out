# HW4 - Let's Network!

We have decided to use Jill and Marika's code for our cache.cc, since our cache.cc had memory leaks. Our previous cache file is renamed old_cache.cc. Our server is located at server.cc; we are using the Crow library: https://github.com/ipkn/crow To use, git clone the crow directory outside of our project. (At the same parent directory as our project). Then, copy cache.hh to crow/include. Then you can compile our server with the line: ```g++-7 -I../crow/include -Wall -Wextra cache.cc server.cc -o server -pthread -lboost_system```. To run the server, use ```./server``` 

Our client is called client.cc. We are using the libcurl library. To use, install the libcurl library: ```sudo apt-get install libcurl4-gnutls-dev```.
To compile the client, enter ```g++ -Wall -Wextra -pedantic client.cc frameworktest.cc -o client -lcurl```.
Run with ```./client``` on a different terminal window. Currently set to work with server address 0.0.0.0:18080

Our tests currently do not pass for the client side, as set (for the client) does not properly work. This is because all of our tests rely on the set function working. However, on the server side, we can clearly see get, delete, and memsize requests going through from the client. To test the server commands, we used curl -X <METHOD> http://127.0.0.1:18080/<param> to test each command/method. Thank you for reading!


# HW2-Hash-it-out
Sierra and Mercy's Cache homework assignment for CSCI 389 (If possible, view on your favorite text editor - Github's README format is messy.)

For Part 3 - Look at HW3_TestingReadme.md for tables and testing info.

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
HW3_TestingReadme.md - Has our tests and tables.
  
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
