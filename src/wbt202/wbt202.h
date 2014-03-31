/** @file wbt202.h */

#ifndef WBT202_H
#define WBT202_H

// Directly mapping the struct to the binary data is likely fail to due
// to memory alignment problems. According to [1], when the type of
// struct-member variables changes, the compiler adds (empty) padding
// bytes. As a result the member variables of the following structs will have
// a wrong offset and the output will be unexpected.
//
// A work-around suggested by [2] makes use of a #pragma-statement,
// which (temporarily) changes the memory alignment. According to that
// source, this work-around works for GNU, Microsoft and Borland
// compilers. Apparently clang (Apple LLVM version 5.0 (clang-500.2.75))
// supports this #pragma-statement as well.
//
// [1] http://stackoverflow.com/a/9852749
// [2] http://solidsmoke.blogspot.com.br/2010/07/woes-of-structure-packing-pragma-pack.html

// By default, assume hardware uses little endian byte order.
#ifndef IS_BIG_ENDIAN
#define IS_BIG_ENDIAN 0
#endif // IS_BIG_ENDIAN

#include <wbt202/wbt202_gps.h>
#include <wbt202/wbt202_log.h>
#include <wbt202/wbt202_sys.h>

#endif // WBT202_H
