#include <iostream>
#include <math.h>
#include <cstring>
#include <sstream>
#include <string>
#include "cache.h"

using std::cin; using std::cout;
using std::endl; using std::stringstream;
using std::stoul; using std::getline;


/**
 *  For a given numerical perspective
 *  checks if positive. non zero and is valid pow of 2
 *  Input: param, an int to check if valid pow2 or pos non-0
 *  Output: true if the number is pos, non-0 pos of 2, false otherwise
 **/
int is_pos_pow2(int param) {
  //checks if 0, if so return false
  if (param == 0) {
    return 0;
  }

  //checks pos and non-0
  int pos = (param > 0);
  //check if square by if sqrt is whole num
  long ceiling = ceil(log2(param));
  int pow = (ceiling - floor(log2(param)) == 0);

  //only returns 1 if positive and pow of 2
  return pow && pos;
}


/**
 *  Checks that the set, block and byte params are valid squares
 *  And checks that byte size is at least 4
 *  Input: argv, an array of command line arguments
 *  Output: 0 if there is no error, 1 if there's an error
 **/
int valid_num_args(char *argv[]) {
  //checks for number input
  if(atoi(argv[1]) == 0 || !is_pos_pow2(atoi(argv[1]))) {
    cout << "Invalid set size argument" << endl;
    return 1;
  }
  //checks if input of correct format
  if(atoi(argv[2]) == 0 || !is_pos_pow2(atoi(argv[2]))) {
    cout << "Invalid block size argument" << endl;
    return 1;
  }
  //checks for number input and for byte of size at least 4
  if(atoi(argv[3]) == 0 || atoi(argv[3]) < 4 || !is_pos_pow2(atoi(argv[3]))) {
    cout << "Invalid byte argument" << endl;
    return 1;
  }
  return 0;
}

/**
 *  Checks that input has correct num of args, check that
 *  non-number params are valid instructions.
 *  Input: argc, argv, number of and command line params
 *  Output: 0 if valid, 1 if invalid
 */
int valid_instruct_args(int argc, char *argv[]) {
  //check proper number of arguments
  if (argc != 7) {
    cout << "Invalid number of arguments" << endl;
    return 1;
  }

  //checks that 4th argument is one of valid options
  if (strcmp(argv[4], "no-write-allocate") != 0 && strcmp(argv[4], "write-allocate") != 0) {
    cout << "Invalid write allocation argument" << endl;
    return 1;
  }

  //checks that 5th argument is one of valid options
  if (strcmp(argv[5], "write-through") != 0 && strcmp(argv[5], "write-back") != 0) {
    cout << "Invalid write through or back argument" << endl;
    return 1;
  }

  //checks that 6th argument is one of valid options
  if (strcmp(argv[6], "lru") != 0 && strcmp(argv[6], "fifo") != 0) {
    cout << "Invalid eviction strategy argument" << endl;
    return 1;
  }

  //checks if no-write-allocate and write-back are combined
  //which wouldn't make sense
  if (strcmp(argv[4], "no-write-allocate") == 0 && strcmp(argv[5], "write-back") == 0) {
    cout << "Error: no-write-allocate and write-back passed together which is invalid" << endl;
    return 1;
  }

  //return valid
  return 0;

}

  
/**
 *  Main fucntion that checks all inputs to be valid
 *  and calls the correct methods, passing the input needed
 *  input: argc, argv, the number of an the command line arguments
 *  output: return 0 if all goes well
 */
int main(int argc, char *argv[]) {

  //first check if input nums are valid
  if (valid_num_args(argv) != 0) {
    return 1;
  }

  //check if other argumnets are valid
  if (valid_instruct_args(argc, argv) != 0) {
    return 1;
  }


  Cache* cache = new Cache(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], argv[6]);
  string op_type;
  string trace_str;
  string trash;
  uint32_t trace;
  pair<uint32_t, uint32_t>* tag_index;
  while (cin) {
    cin >> op_type;
    cin >> trace_str;
    cin >> trash;
    trace_str = trace_str.substr(2);
    trace = stoul(trace_str, 0, 16);
    tag_index = cache->process_address(trace);
    if (op_type.compare("l") == 0) {
      cache->read_cache(tag_index->first, tag_index->second);
    } else if (op_type.compare("s") == 0) {
      cache->write_cache(tag_index->first, tag_index->second);
    }
    op_type = "a";
  }
  
  cout << cache->get_stats()->to_string();

  return 0;
  
  //cout << "Hello World" << endl;
}
