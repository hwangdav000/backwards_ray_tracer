#include "main.h"


int main(int argc, char *argv[]){
  //  case $./mymake textfile
  if (argc == 2) {
    if (process_file(argv[1]) != 0) {
      fprintf(stderr, "error: invalid file \n");
      exit(EXIT_FAILURE);
    }
    //  parses line in text file
    if (init_vars()  != 0) {
      fprintf(stderr, "error: initializing variables \n");
      exit(EXIT_FAILURE);
    }
    //  builds ppm file
    setVar();
    init_array();
    build_PPM();
    deallocate_array();

    //  show program has completed
    printf("Program Complete\n");
  }
  else {
    //  incorrect number of arguments supplied
    fprintf(stderr, "error: format args\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
