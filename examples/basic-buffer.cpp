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
