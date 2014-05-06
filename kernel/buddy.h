#include "common.h"
#include "multiboot.h"
//page size 4k
#define PAGE_SIZE   0x1000
//max page = 2^32 / 2^12
//#define MAX_PAGE    0x100000
#define MAX_PAGE    0x1000
//null page 
#define NULL_PAGE   0x100001

#define MAX_SIZE 32768

#define AVAI_COUNT 11

typedef struct _chunk {

    u32 begin;
    u32 end;
    u32 pre     :   21;
    u32 next    :   21;
    u32 size    :   20;
    u32 avai    :   1;
    u32 ini     :   1;

}__attribute__((packed)) chunk;


int k_malloc( u32 f_size );
int k_free(u32 begin);
void ini_buddy(multiboot_head_t *mboot_ptr);
void listmem();
