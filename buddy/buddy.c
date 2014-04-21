#include <stdio.h>
#include <stdlib.h>

//page size 4k
#define PAGE_SIZE   0x1000
//max page = 2^32 / 2^12
#define MAX_PAGE    0x100000
//null page 
#define NULL_PAGE   0x100001

#define MAX_SIZE 32768

#define AVAI_COUNT 11

typedef unsigned int u32;
typedef char u8;
typedef struct _chunk {

    u32 begin;
    u32 end;
    u32 pre     :   21;
    u32 next    :   21;
    u32 size    :   20;
    u32 avai    :   1;
    u32 ini     :   1;

}__attribute__((packed)) chunk;

//mem[0] always be head
chunk mem[MAX_PAGE];
int avi_size[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}; //11

static u32 findpos(){
    u32 i;
    for (i = 1; i < MAX_PAGE; i++) {
      if(mem[i].ini == 0)
        return i;
    }
    return -1;
}

static void inimem(u32 begin, u32 end){
    u32 pos = findpos();
    mem[pos].begin = begin;
    mem[pos].end = end;
    mem[pos].size = (end - begin + 1) / PAGE_SIZE;
    mem[pos].pre = pos == 0 ? NULL_PAGE : pos -1;
    mem[pos].next = NULL_PAGE;
    mem[pos].avai = 1;
    mem[pos].ini = 1;

    u32 pre = mem[pos].pre; 
    if(pre != NULL_PAGE ){
        mem[pre].next = pos;
    }
}

static int split( u32 pos, u32 size ){
printf("first in pos:%d size:%d\n",pos,size);
    //1 2 4 8 16 32 64 256 65536
    if( mem[pos].size <= size )return -1;
    if( size < MAX_SIZE ){
        int ret = split(pos, size == 1 ? 2 : size*2 );
        pos = ret == -1 ? pos : ret;
    }
    printf("begin split pos:%d size:%d\n",pos,size);
    
    chunk* pre = mem[pos].pre != NULL_PAGE ? &mem[ mem[pos].pre ] : -1;
    chunk* now = &mem[pos];
    u32 new_pos = findpos();

    if(new_pos == -1)return -1;

    chunk* new = &mem[new_pos];

    new->begin = now->begin;
    new->end = new->begin + 0x1000 * size - 1;
    new->size = size;
    new->avai = 1;
    new->ini = 1;
    new->next = pos;
    new->pre = now->pre;

    now->begin = new->end + 1;
    now->size = (now->end - now->begin + 1) / PAGE_SIZE;
    now->pre = new_pos;

    if((u32)pre != -1)
        pre->next = new_pos;

    return new_pos;

}
int k_malloc( u32 f_size ){
 
     int i;
     for (i = 0; i <= AVAI_COUNT; i++) {
         if(i == AVAI_COUNT)
             return -1; //max is AVAI_COUNT-1, error occurs when i = AVAI_COUNT
         if(avi_size[i] == f_size)
             break;
     }
     
    //search
    int fit = -1; u32 t_head = 0;
 
    while( t_head != NULL_PAGE && mem[t_head].ini != 0 ){
        chunk* ch = &mem[t_head];
        if(ch->avai==1 && ch->size==f_size){
            //find
            ch->avai = 0;
            return ch->begin;
        }
        if(ch->avai==1 && ch->size > f_size && fit == -1)
            fit = t_head;
 
        t_head = mem[t_head].next;
    }
 
    if(fit == -1)return -1;
    printf("fit:%d\n",fit);
    t_head = split(fit, f_size);     
 
    if(t_head == -1)return -1;
 
    mem[t_head].avai = 0;
    return mem[t_head].begin;
}

static void merge(u32 pos){
    //only merge next 
    chunk* pre = &mem[ mem[pos].pre ];
    chunk* now = &mem[pos];
    chunk* next = &mem[ mem[pos].next ];
    if( next->size == now->size && next->avai == 1 && next->begin == now->end+1 ){
        next->begin = now->begin;
        next->size = next->size*2;

        next->pre = now->pre;
        pre->next = now->next;

        now->ini=0;
        merge(now->next);
    }
}

int k_free(u32 begin){
    

   u32 pos=-1, t_head = 0;
   //search
   while( t_head != NULL_PAGE && mem[t_head].ini != 0 ){
        if(t_head!=0 && mem[t_head].begin == begin){
            pos = t_head;
            break;
        }
       t_head = mem[t_head].next;
   }
   if(pos == -1)return -1;

   mem[pos].avai = 1;

   //merge
   merge(pos);
   return 1;

}

void listmem(){
    printf("========list mem======\n");
    printf("%5s%10s%10s%10s%10s%10s%10s\n","id","begin", "end","pre","next","avai","size");
    u32 t_head = 0;
    while( t_head != NULL_PAGE && mem[t_head].ini != 0 ){
        chunk ch = mem[t_head];
        printf("%5d", t_head);
        printf("%10x%10x", ch.begin, ch.end);
        printf("%10d%10d", ch.pre, ch.next);
        printf("%10d%10d\n", ch.avai,ch.size);
        t_head = mem[t_head].next;
    }
}

u32 testmalloc(u32 size){
  u32 ret;
  printf("begin malloc %d\n", size);
  printf("malloc %d result: %x\n",size ,ret=k_malloc(size) );
  listmem();
  return ret;
}
void testfree(u32 addr){
  printf("free addr:%x\n",addr);
  k_free(addr);
  listmem();

}

int main(int argc, const char *argv[])
{
  memset(mem, 0, sizeof(chunk)*MAX_PAGE);
  mem[0].pre = NULL_PAGE;
  mem[0].next = 1;
  mem[0].ini = 1;
  /*  test case
   *  head must be 4k aligned
   *  0x00000 ~ 0x9f000
   *  0x100000 ~ 0x1EF0000
   */
  inimem(0x00000, 0x9F000);
  inimem(0x100000, 0x1EF0000);
  listmem();
  testmalloc(15);
  u32 addr1 = testmalloc(1024);
  u32 addr2 = testmalloc(16);
  u32 addr3 = testmalloc(2);
  u32 addr4 = testmalloc(2);
  testfree(addr4);
  testfree(addr3);
  testfree(addr2);
  testfree(addr1);
  
  return 0;
}
