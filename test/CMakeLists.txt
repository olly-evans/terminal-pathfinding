include(CTest)

add_executable(test_grid test_grid.c)
target_link_libraries(test_grid PRIVATE app_lib)
add_test(NAME grid_test COMMAND test_grid)