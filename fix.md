# 问题1
```sh
uname -a
Linux wxg-Aspire-GX-781 5.19.0-46-generic #47~22.04.1-Ubuntu SMP PREEMPT_DYNAMIC Wed Jun 21 15:35:31 UTC 2 x86_64 x86_64 x86_64 GNU/Linux

gcc -v
gcc version 9.5.0 (Ubuntu 9.5.0-1ubuntu1~22.04)

./tools/libarch-debug FD7BB9A9
libarch-debug: malloc.c:2617: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
```

## 内存分析
```cpp
// 能正常输出结果
valgrind --leak-check=full --track-origins=yes -s --log-file="mem.log" ./tools/libarch-debug FD7BB9A9
==103490== Memcheck, a memory error detector
==103490== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==103490== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==103490== Command: ./tools/libarch-debug FD7BB9A9
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A044: decode_load_store_register_pair (load-and-store.c:600)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c0d0 is 0 bytes inside a block of size 4 alloc'd
==103490==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EEED: libarch_instruction_add_field (instruction.c:281)
==103490==    by 0x13A044: decode_load_store_register_pair (load-and-store.c:600)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A05B: decode_load_store_register_pair (load-and-store.c:601)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c128 is 0 bytes after a block of size 8 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A05B: decode_load_store_register_pair (load-and-store.c:601)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A072: decode_load_store_register_pair (load-and-store.c:602)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c180 is 4 bytes after a block of size 12 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A072: decode_load_store_register_pair (load-and-store.c:602)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A089: decode_load_store_register_pair (load-and-store.c:603)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c1d8 is 8 bytes after a block of size 16 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A089: decode_load_store_register_pair (load-and-store.c:603)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A0A0: decode_load_store_register_pair (load-and-store.c:604)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c230 is 12 bytes after a block of size 20 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A0A0: decode_load_store_register_pair (load-and-store.c:604)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A0B7: decode_load_store_register_pair (load-and-store.c:605)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c298 is 16 bytes after a block of size 24 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A0B7: decode_load_store_register_pair (load-and-store.c:605)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A0CE: decode_load_store_register_pair (load-and-store.c:606)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c300 is 20 bytes after a block of size 28 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A0CE: decode_load_store_register_pair (load-and-store.c:606)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== Conditional jump or move depends on uninitialised value(s)
==103490==    at 0x12DAAD: create_string (libarch-debug.c:161)
==103490==    by 0x12DF60: disassemble (libarch-debug.c:252)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Uninitialised value was created by a heap allocation
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12E235: _libarch_instruction_realloc_operand (instruction.c:39)
==103490==    by 0x12E458: libarch_instruction_add_operand_immediate_with_fix_extra (instruction.c:89)
==103490==    by 0x13A4EE: decode_load_store_register_pair (load-and-store.c:696)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
stp     x29, x30, [sp, -112]!
==103490== 
==103490== HEAP SUMMARY:
==103490==     in use at exit: 364 bytes in 3 blocks
==103490==   total heap usage: 13 allocs, 10 frees, 1,856 bytes allocated
==103490== 
==103490== 364 (80 direct, 284 indirect) bytes in 1 blocks are definitely lost in loss record 3 of 3
==103490==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12E2B8: libarch_instruction_create (instruction.c:53)
==103490==    by 0x12DF1F: disassemble (libarch-debug.c:244)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== LEAK SUMMARY:
==103490==    definitely lost: 80 bytes in 1 blocks
==103490==    indirectly lost: 284 bytes in 2 blocks
==103490==      possibly lost: 0 bytes in 0 blocks
==103490==    still reachable: 0 bytes in 0 blocks
==103490==         suppressed: 0 bytes in 0 blocks
==103490== 
==103490== ERROR SUMMARY: 9 errors from 9 contexts (suppressed: 0 from 0)
==103490== 
==103490== 1 errors in context 1 of 9:
==103490== Conditional jump or move depends on uninitialised value(s)
==103490==    at 0x12DAAD: create_string (libarch-debug.c:161)
==103490==    by 0x12DF60: disassemble (libarch-debug.c:252)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Uninitialised value was created by a heap allocation
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12E235: _libarch_instruction_realloc_operand (instruction.c:39)
==103490==    by 0x12E458: libarch_instruction_add_operand_immediate_with_fix_extra (instruction.c:89)
==103490==    by 0x13A4EE: decode_load_store_register_pair (load-and-store.c:696)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 2 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A0CE: decode_load_store_register_pair (load-and-store.c:606)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c300 is 20 bytes after a block of size 28 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A0CE: decode_load_store_register_pair (load-and-store.c:606)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 3 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A0B7: decode_load_store_register_pair (load-and-store.c:605)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c298 is 16 bytes after a block of size 24 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A0B7: decode_load_store_register_pair (load-and-store.c:605)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 4 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A0A0: decode_load_store_register_pair (load-and-store.c:604)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c230 is 12 bytes after a block of size 20 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A0A0: decode_load_store_register_pair (load-and-store.c:604)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 5 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A089: decode_load_store_register_pair (load-and-store.c:603)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c1d8 is 8 bytes after a block of size 16 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A089: decode_load_store_register_pair (load-and-store.c:603)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 6 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A072: decode_load_store_register_pair (load-and-store.c:602)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c180 is 4 bytes after a block of size 12 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A072: decode_load_store_register_pair (load-and-store.c:602)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 7 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A05B: decode_load_store_register_pair (load-and-store.c:601)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c128 is 0 bytes after a block of size 8 alloc'd
==103490==    at 0x484DCD3: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EF2D: libarch_instruction_add_field (instruction.c:283)
==103490==    by 0x13A05B: decode_load_store_register_pair (load-and-store.c:601)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== 
==103490== 1 errors in context 8 of 9:
==103490== Invalid write of size 8
==103490==    at 0x12EF6F: libarch_instruction_add_field (instruction.c:288)
==103490==    by 0x13A044: decode_load_store_register_pair (load-and-store.c:600)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490==  Address 0x4a9c0d0 is 0 bytes inside a block of size 4 alloc'd
==103490==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==103490==    by 0x12EEED: libarch_instruction_add_field (instruction.c:281)
==103490==    by 0x13A044: decode_load_store_register_pair (load-and-store.c:600)
==103490==    by 0x13BC15: disass_load_and_store_instruction (load-and-store.c:1144)
==103490==    by 0x12F086: libarch_disass (instruction.c:335)
==103490==    by 0x12DF2F: disassemble (libarch-debug.c:246)
==103490==    by 0x12E190: main (libarch-debug.c:276)
==103490== 
==103490== ERROR SUMMARY: 9 errors from 9 contexts (suppressed: 0 from 0)
```

## 调试
```cpp
gdb --args ./tools/libarch-debug FD7BB9A9

#0  decode_load_store_register_pair (instr=0x7fffffffd858) at /home/wxg/test/libarch/src/decoder/load-and-store.c:615
(gdb) p {opc,V,L,imm7,Rt2,Rn,Rt}
$5 = {2, 0, 0, 114, 30, 31, 29}

b create_string
$8 = {parsed = 0x0, opcode = 2847505405, addr = 0, group = 0, subgroup = 9, type = ARM64_INSTRUCTION_STP, cond = -1, spec = -1, 
  operands = 0x5555555a7340, operands_len = 4, fields = 0x5555555a7300, fields_len = 7}
(gdb) p instr->operands[0]
$10 = {op_type = 17 '\021', reg = 29, reg_size = 64 '@', reg_type = 1 '\001', shift = 0, shift_type = 0 '\000', imm_bits = 0, imm_type = 0 '\000', 
  imm_opts = 0, target = 0x0, extra = 0, extra_val = 0, prefix = 0 '\000', suffix = 0 '\000', suffix_extra = 0 '\000'}

b libarch_instruction_add_operand_register
(gdb) p opcode_table[i]
$15 = {select = 3, opc = 2, V = 0, L = 0, width = 64, simd_fp = 1, type = ARM64_INSTRUCTION_STP}
(gdb) n
696                     libarch_instruction_add_operand_immediate_with_fix_extra (instr, *(int *) &imm, ARM64_IMMEDIATE_TYPE_INT, 0, ']');
(gdb) p /x imm
$16 = 0xffffff90
(gdb) p /x -imm
$17 = 0x70
```