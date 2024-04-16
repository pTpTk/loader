#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h>

typedef int(*voidFunc)(void);

int main(int argc, char* argv[])
{
  char* buffer;
  voidFunc mainFunc;
  struct stat myfilestats;
  int fd;
  int* addr;

  fd = open(argv[1], O_RDONLY);
  fstat(fd, &myfilestats);
  *addr = 0x08048000;
  buffer = (char*)mmap(addr, myfilestats.st_size, PROT_EXEC, MAP_PRIVATE, fd, 0);
  close(fd);

  mainFunc = ((voidFunc)(buffer + 0x1000));

  mainFunc();

  munmap(buffer, myfilestats.st_size);

  return EXIT_SUCCESS;
}