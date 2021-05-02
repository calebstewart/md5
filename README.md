# MD5 Hash Library

While there are other implementations of the MD5 hashing algorithm, I wrote this
library with the intention of being used on embedded platforms (such as Arduino).
However, it is not restricted to Arduino.

I can't take credit for the algorithm implementation itself. I mostly ripped that
from [here](https://github.com/tzikis/ArduinoMD5/). I had issues with that library
mainly related to it's use of `malloc` and general bad OOP principles. This library
should be more straightforward to use and has no dynamically allocated memory.

## Principles

This library will not allocate any memory and works off of stack variables or
existing memory space passed into the methods from the library user. The following
should be kept in mind:

- Digests are always 33 character strings (hex-encoded hash plus null-terminator).
- Hashes are always byte arrays of 16 characters. They are not null-terminated.
- If a pointer is not `const`, it will be modified by the method.
- Calling `MD5::finalize` **does not** reset the internal MD5 state.

## Example - Basic String Hashing

If you have a string in memory you need to hash, you can use the `MD5::hash` helper
method to calculate the hash.

```cpp
#include <iostream>
#include <md5.h>

int main(int argc, char** argv)
{
  char digest[33];
  unsigned char hash[16];

  // Write the calculated hash to `hash`
  MD5::hash("hello world\n", hash);
  // Retrieve the hex-encoded digest
  MD5::digest(hash, digest);

  std::cout << "md5(\"hello world\\n\") => \"" << digest << "\"\n";

  return 0;
}
```

## Example - Basic Buffer Hashing

If you have a buffer of known length that you would like to hash, you can use the
`MD5::hash` helper method to calculate the hash similar to the method used for
strings.

```cpp
#include <iostream>
#include <md5.h>

int main(int argc, char** argv)
{
  char digest[33];
  unsigned char hash[16];
  unsigned char data[10] = {1,2,3,4,5,6,7,8,9,10};

  // Write the calculated hash to `hash`
  MD5::hash(data, 10, hash);
  // Retrieve the hex-encoded digest
  MD5::digest(hash, digest);

  std::cout << "md5({1,2,3,4,5,6,7,8,9,10}) => \"" << digest << "\"\n";

  return 0;
}
```

## Example - Iterative Hashing

MD5 is an iterative process, which can be fed data as it is streamed. If you are
generating or reading data, you can feed the data in chunks instead of storing
the entire buffer in memory at once.

```cpp
#include <iostream>
#include <fstream>
#include <md5.h>

int main(int argc, char** argv)
{
  char digest[33];
  unsigned char hash[16];
  char chunk[512];
  MD5 md5;
  std::fstream data_file;

  // Open the executable itself for reading
  data_file.open(argv[0], std::ios::in);

  // Read until there's no more data and add it to the hash
  do {
    data_file.read(chunk, 512);
    md5.update(chunk, data_file.gcount());
  } while ( ! data_file.eof() );

  // Retrieve the final hash
  md5.finalize(hash);

  // If you'd like to reuse the MD5 object to calculate new hashes,
  // you must call reset to ensure you don't continue calculating from
  // the previous data.
  // md5.reset();

  // Output a hex digest
  MD5::digest(hash, digest);
  std::cout << "md5sum " << argv[0] << " => \"" << digest << "\"\n";

  return 0;
}
```
