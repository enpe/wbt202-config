# Tests
add_executable( test_memory_alignment test_memory_alignment.cpp )
add_executable( test_endianness       test_endianness.cpp       )
add_executable( test_gps_checksums    test_gps_checksums.cpp    )

target_link_libraries( test_memory_alignment wbt202 )
target_link_libraries( test_endianness       wbt202 )
target_link_libraries( test_gps_checksums    wbt202 )

add_test( NAME MEMORY_ALIGNMENT COMMAND test_memory_alignment                                            )
add_test( NAME ENDIANNESS       COMMAND test_endianness                                                  )
add_test( NAME GPS_CHECKSUMS    COMMAND test_gps_checksums "${CMAKE_SOURCE_DIR}/data/WBT202/SYS/GPS.BIN" )
