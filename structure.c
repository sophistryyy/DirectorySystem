#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
// #include <arpa/inet.h>

struct __attribute__((__packed__)) superblock_t {
    uint8_t   fs_id [8];  //8 bytes
    uint16_t block_size;  //2
    uint32_t file_system_block_count;  //4
    uint32_t fat_start_block;  //4
    uint32_t fat_block_count;  //4
    uint32_t root_dir_start_block; //4
    uint32_t root_dir_block_count;  //4
};


void main(int argc, char* argv[]) {

    int fd = open(argv[1], O_RDWR); //open file
    struct stat buffer;
    int status = fstat(fd, &buffer);

    //tamplate:   pa=mmap(addr, len, prot, flags, fildes, off);
    //c will implicitly cast void* to char*, while c++ does NOT
    void* address=mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    struct superblock_t* sb;
    sb=(struct superblock_t*)address;
    printf("block count in struct: %d\n", ntohl(sb->file_system_block_count));

    /*int fssize;
    memcpy(&fssize, address+10, 4);
    fssize=ntohl(fssize);
    printf("block count: %x\n",fssize);
    */

    munmap(address,buffer.st_size);
    close(fd);
}
