#ifndef _MD5_H_
#define _MD5_H_

#include <sys/types.h>

class MD5
{
  public:
    MD5();

    // Reset internal state
    void reset();

    // Add data to the interative hash solution
    void update(const void* data, size_t length);

    // Finalize the hash to the given 16-byte buffer
    // This **does not** reset the internal state.
    void finalize(unsigned char* hash);

  public:

    // Calculate the hash of the given null-terminated string constant
    static void hash(const char* str, unsigned char* hash);
    // Calculate the hash of the given buffer
    static void hash(const void* buffer, size_t size, unsigned char* hash);
    // Produce a hex digest of the given hash
    static void digest(const unsigned char* hash, char* digest);

  private:

    const void* process(const void* data, size_t length);

  private:
    unsigned long lo, hi;
    unsigned long a, b, c, d;

    unsigned char buffer[64];
    unsigned long block[16];
};

#endif

