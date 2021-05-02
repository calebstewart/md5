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
