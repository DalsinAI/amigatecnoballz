/* Included before every C++ file (-include): the C++ streams first, since
 * the toolchain's pthread.h wraps read(), write() and close() in
 * cancellation macros once <unistd.h> is in, which breaks <istream> and
 * <fstream> read after it. The AmiCradle Team. GPL 3 or later, like
 * TecnoballZ. */
#include <iostream>
#include <fstream>
#include <sstream>
