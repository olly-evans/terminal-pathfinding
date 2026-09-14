include(CTest)

add_executable(test_grid test_grid.c)
target_link_libraries(test_grid PRIVATE app_lib)
add_test(NAME grid_test COMMAND test_grid)

add_executable(test_abuf test_abuf.c)
target_link_libraries(test_abuf PRIVATE app_lib)
add_test(NAME abuf_test COMMAND test_abuf)

add_executable(test_heap test_heap.c)
target_link_libraries(test_heap PRIVATE app_lib)
add_test(NAME heap_test COMMAND test_heap)