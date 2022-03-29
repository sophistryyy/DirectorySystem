#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <arpa/inet.h>

//superblock
struct __attribute__((__packed__)) superblock_t {
    uint8_t   fs_id [8];  //8 bytes
    uint16_t block_size;  //2
    uint32_t file_system_block_count;  //4
    uint32_t fat_start_block;  //4
    uint32_t fat_block_count;  //4
    uint32_t root_dir_start_block; //4
    uint32_t root_dir_block_count;  //4
};

//timedate entry
struct __attribute__((__packed__)) dir_entry_timedate_t {
    uint16_t yearl;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

//directory entry
struct __attribute__((__packed__)) dir_entry_t{
    uint8_t status;
    uint32_t starting_block;
    uint32_t block_count;
    uint32_t size;
    struct dir_entry_timedate_t create_time;
    struct dir_entry_timedate_t modify_time;
    uint8_t filename[31];
    uint8_t unused[6];
};

int diskinfo(char* filename){
    int fd = open(filename, O_RDWR); //open file
    struct stat buffer;
    int status = fstat(fd, &buffer);
    // printf("%s\n",buffer.st_size); //gives file size

    //template:   pa=mmap(addr, len, prot, flags, fildes, off);
    //c will implicitly cast void* to char*, while c++ does NOT
    void* address=mmap(NULL, buffer.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    struct superblock_t* sb;
    sb=(struct superblock_t*)address;

    //iterate through fat table
    //start at block fat_start_block, read fat_block_count blocks

    // int fssize;
    // memcpy(&fssize, address+10, 4);
    // fssize=ntohl(fssize);
    // printf("block count: %x\n",fssize);
    
    print_diskinfo(sb);
    munmap(address,buffer.st_size);
    close(fd);
    return 0;
}

void print_diskinfo(struct superblock_t* sb){
    printf("Super block information:\n");
    printf("Block size: %d\n", ntohs(sb->block_size));
    printf("Block count: %d\n", ntohl(sb->file_system_block_count));
    printf("FAT starts: %d\n", ntohl(sb->fat_start_block));
    printf("FAT blocks: %d\n", ntohl(sb->fat_block_count));
    printf("Root directory start: %d\n", ntohl(sb->root_dir_start_block));
    printf("Root directory blocks: %d\n\n", ntohl(sb->root_dir_block_count));
    printf("FAT information:\n");
    printf("Free blocks: d\n");
    printf("Reserved blocks: d\n");
    printf("Allocated blocks: d\n");
}

void disklist(){
    return;
}

void diskget(){
    return;
}

void diskput(){
    return;
}

void diskfix(){
    return;
}

int main(int argc, char* argv[]){   
    char* file;

    //get filename from args
	if (argc < 2) {
		fprintf(stderr, "Usage: Can you spare some arguments?\n");
	} else {
        file = argv[1];
	}

    //an interesting way to have multiple .o files but only one .c file
    #if defined(PART1)
        diskinfo(file);
    #elif defined(PART2)
        disklist(file);
    #elif defined(PART3)
        diskget(file);
    #elif defined(PART4)
        diskput(file);
    #elif defined(PART5)
        diskfix(file);
    #else
        #error "PART[12345] must be defined"
    #endif
        return 0;
}