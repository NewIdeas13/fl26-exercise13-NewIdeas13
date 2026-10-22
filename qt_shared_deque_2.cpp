// qt_shared_deque_2.cpp
#include <iostream>
#include <limits>

#include "shared_ring_buffer.h"

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  if(!buffer.create(100)){
    std::cerr << "Could not create/attach shared memory" << std::endl;
    return 1;
  }

  while(true){
    int value;
    std::cout << "$>";

    if(!(std::cin >> value)){
      if(std::cin.eof()){
        break; // Ctrl+D: exit cleanly so the destructor detaches
      }
      // not a number (e.g. "abc"): clear the error and discard the bad line
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Please enter an integer." << std::endl;
      continue;
    }

    if(buffer.enqueue(value)){
      std::cout << "Enqueued: " << value << std::endl;
    }
    else{
      std::cout << "Queue is full, " << value << " was not enqueued" << std::endl;
    }
  }

  return 0;
}