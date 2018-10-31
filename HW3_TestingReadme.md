
|Desc|Func|Evaluation|
|----|----|--------|
|test_space_used|test_space_used()|PASSED|
|test_insert|test_insert()|PASSED|
|query_key|test_query()|PASSED|
|query_uninserted_key|test_query_uninserted()|PASSED|
|modify_stored_value|test_inset_and_mod()|PASSED|
|delete key space used|test_insert_and_delete|PASSED|
|query doesn't mod memused|test_delete_and_query()|PASSED|
|empty del doesn't change mem|test_delete_uninserted()|PASSED|
|test_evict|test_evict()| PASSED|




Laura and Lucus 5/9

When testing Laura and Lucus's code, we did not encounter any compiling errors. However, some of our assertions (REQUIRE, since we used Catch2) failed. For one test, Modify_stored_value, the pointer returned was not the same as the pointer that was originally stored. In other tests, the space_used() was not the expected value. For example, the space_used after deleting an item did not decrement, as well as after evictions. Other than that, the rest of the tests passed.

|Test|Eval|
|----|----|
|test_space_used|PASSED|
|test_insert|PASSED|
|query_key|PASSED|
|query_uninserted_key|PASSED|
|modify_stored_value|FAILED|
|delete key (space used|FAILED|
|query doesn't mod memused|FAILED|
|empty del doesn't change mem|PASSED|
|test_evict|FAILED|


Josh and Ryan 6/9

When testing Josh and Ryan's code, we did encounter a few warnings when compiling. Most were initialization issues ("blah_ will be initialized after [...]"). None of the warnings had a major impact on our testing. A few tests failed, however. The pointer value for a value was not the same after querying and modifying the value. Also, the space_used did not update after eviction occurs. Other than that, the rest of the tests passed.

|Test|Eval|
|----|----|
|test_space_used|PASSED|
|test_insert|PASSED|
|query_key|FAILED|
|query_uninserted_key|PASSED|
|modify_stored_value|FAILED|
|delete key (space used|PASSED|
|query doesn't mod memused|PASSED|
|empty del doesn't change mem|PASSED|
|test_evict|FAILED|


Kathy and Rhody 9/9

When testing Kathy and Rhody's code, we got a few warnings when compiling. Those were just unused parameters however, nothing serious. All of our tests passed!

|Test|Eval|
|----|----|
|test_space_used|PASSED|
|test_insert|PASSED|
|query_key|PASSED|
|query_uninserted_key|PASSED|
|modify_stored_value|PASSED|
|delete key (space used|PASSED|
|query doesn't mod memused|PASSED|
|empty del doesn't change mem|PASSED|
|test_evict|PASSED|

