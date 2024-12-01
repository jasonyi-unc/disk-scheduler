#define _GNU_SOURCE // allows us to use O_DIRECT
#define BUFFER_ALIGN 512 // align buffer to 512 bytes for O_DIRECT
#define GB_IN_BYTES 1024*1024*1024
#define MB_512_IN_BYTES 512*1024*1024

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>


void perform_io_test(const char *file_path, size_t io_size, size_t stride, 
                     int is_random, int is_write, size_t total_size, size_t desired_iops);


int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Too few arguments!\n");
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    bool is_io_size = atoi(argv[2]) != 0;
    bool is_stride = atoi(argv[3]) != 0;
    bool is_random = atoi(argv[4]) != 0;
    bool is_write = atoi(argv[5]) != 0;

    // List of sizes in KB
    size_t sizes[] = {4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 
                         4096, 8192, 16384, 32768, 65536, 102400};
    size_t num_sizes = sizeof(sizes) / sizeof(sizes[0]);


    if(is_io_size) {
        printf("I/O size tests\n");
        // I/O size tests
        for (size_t i = 0; i < num_sizes; ++i) {
            size_t size = sizes[i] * 1024; // Convert KB to bytes
            printf("-------------------------------------------------------\n");
            printf("Testing I/O size: %zu KB\n\n", sizes[i]);

            for(int j = 0; j < 5; ++j) {
                perform_io_test(file_path, size, 0, is_random, is_write, GB_IN_BYTES, GB_IN_BYTES);
            }
        }
    }

    if(is_stride) {
        printf("Stride tests\n");
        // stride tests

        size_t io_sizes_in_kb[] = {
            1 * 1024, // 1 MB = 1,024 KB
            3 * 1024, // 3 MB = 3,072 KB
            5 * 1024, // 5 MB = 5,120 KB
            8 * 1024, // 8 MB = 8,192 KB
            10 * 1024 // 10 MB = 10,240 KB
        };

        for (size_t i = 0; i < 5; ++i) {
            size_t io_size = io_sizes_in_kb[i] * 1024; // Convert KB to bytes

            printf("**********************************************************\n");
            printf("Testing I/O size: %zu KB\n", io_sizes_in_kb[i]);


            for (size_t j = 0; j < num_sizes; ++j) {
                size_t stride_size = sizes[i] * 1024; // Convert KB to bytes
                printf("-------------------------------------------------------\n");
                printf("Testing stride size: %zu KB\n\n", sizes[i]);

                // 5 runs per stride size
                for (size_t k = 0; k < 5; ++k) {
                    perform_io_test(file_path, io_size, stride_size, is_random, is_write, GB_IN_BYTES, GB_IN_BYTES);
                }
            
            }
        }

    }
    
    return 0;
}


void perform_io_test(const char *file_path, size_t io_size, size_t stride,
                     int is_random, int is_write, size_t total_size, size_t desired_iops) {    
    int flags = O_RDWR | O_CREAT;

    // checks if the program is being compiled on a Linux system
    #ifdef __linux__
        flags |= O_DIRECT; // requests direct I/O, which ensures all file I/O operations go directly to the disk
    #endif

    // open the file
    int fd = open(file_path, flags, 0666);
    if (fd == -1) {
        perror("Failed to open file");
        return;
    }

    // allocate aligned memory for buffer
    void *buffer;
    if (posix_memalign(&buffer, BUFFER_ALIGN, io_size) != 0) {
        perror("posix_memalign failed");
        exit(EXIT_FAILURE);
    }
    memset(buffer, 0, io_size);

    size_t total_iops = 0;
    size_t offset = 0;

    // used to represent time with high precision
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time); // syscall that retrieves current time


    while (total_iops < desired_iops) {     
        if (is_random) {
            // Generate a random offset within the valid range
            offset = (rand() % ((total_size - io_size) / io_size)) * io_size;
        } else {
            offset += io_size + stride;
            offset = (offset / BUFFER_ALIGN) * BUFFER_ALIGN;
        }

        // SSD in Adams is 512 MB, so this stays below it
        if (offset + io_size > MB_512_IN_BYTES) {
            offset = offset % (1024 * 1024 * 512);
        }

        offset = offset - offset % 4096;
        
           
        // seek to the offset
        if (lseek(fd, offset, 0) == -1) {
            perror("lseek failed");
            break;
        }

        ssize_t result;
        // perform write or read
        if (is_write) {
            result = write(fd, buffer, io_size);
        } else {
            result = read(fd, buffer, io_size);
        }

        if (result == -1) {
            perror("I/O operation failed");
            break;
        }

        // sync after write
        if (is_write) {
            fsync(fd);
        }


        total_iops += io_size;
    }

    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    double throughput = (total_iops / elapsed_time) / (1024 * 1024); // convert to MB/s

    printf("%s Test\n", is_write ? "Write" : "Read");
    printf("IO Size: %.2f KB, Stride: %.2f KB, Mode: %s\n", 
           io_size / 1024.0, stride / 1024.0, is_random ? "Random" : "Sequential");
    printf("Throughput: %.2f MB/s\n", throughput);
    printf("\n");


    // cleanup
    close(fd);
    free(buffer);

}