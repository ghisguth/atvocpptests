include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(tests tests.cpp)
target_link_libraries(tests m)

add_executable(volat volat.cpp)
target_link_libraries(volat m boost_thread-mt)

add_executable(volat_barrier volat_barrier.cpp)
target_link_libraries(volat_barrier m boost_thread-mt)

add_executable(atomic_barrier atomic_barrier.cpp)
target_link_libraries(atomic_barrier m boost_thread-mt)

add_executable(volat_minimal volat_minimal.cpp)
target_link_libraries(volat_minimal m boost_thread-mt)
