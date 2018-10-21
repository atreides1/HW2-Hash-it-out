# HW2-Hash-it-out
Sierra and Mercy's Cache homework assignment for CSCI 389

Important Files: 
cache.hh - Unmodified header file used to guide cache implementation
cache.cc - Creates a cache using an unordered map of key/value pairs, then an ordered map of key/size pairs.
Since storage and access is all to the unoredered map, it allowed us to include functionality that utilized 
umap's included properites:
  umap uses its own hash function, but also allows you to set your own if included in the parameters during initialization.
    for our purposes, with implemented this using a lambda function
  umap uses buckets when hasing, which allows us to avoid collisions
  max_load_factor() allows us to set the load factor of our umap, allowing for dynamic resizing
  count(key) allows us to see the number of items for a given hashed bucket in umap so we can tell if there's a value stored somewhere
  
The eviction policy uses FIFO. The key/vals are in umap and the key/index_sizes are in a regular map. Since the regular map is in 
order, our evictor_FIFO() finds the first key in the key_bytes map, then deletes the stored values in key_bytes AND storage using the key.

test.cc - Creates a set of functions that test behavior on the edge such as deleting nonexistant keys, general querying, 
and querying for a key that wasn't inserted then calls all functions in main.
