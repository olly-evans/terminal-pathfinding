include(CTest)

add_executable(test_grid test_grid.c)
target_link_libraries(test_grid PRIVATE pathfinding_core)
add_test(NAME grid_test COMMAND test_grid)