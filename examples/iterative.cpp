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
