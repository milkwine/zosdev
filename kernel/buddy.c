#include "common.h"
#include "buddy.h"
#include "multiboot.h"
#include "monitor.h"

//mem[0] always be head
chunk mem[MAX_PAGE];
int avi_size[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}; //11

static u32 findpos();
static void addmem(u32 begin, u32 end);
static int split( u32 pos, u32 size );
static void merge(u32 pos);

static u32 findpos(){
    u32 i;
    for (i = 1; i < MAX_PAGE; i++) {
      if(mem[i].ini == 0)
        return i;
    }
    return -1;
}

static void addmem(u32 begin, u32 end){
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

    if( mem[pos].size <= size )return -1;
    if( size < MAX_SIZE ){
        int ret = split(pos, size == 1 ? 2 : size*2 );
        pos = ret == -1 ? pos : ret;
    }
    
    chunk* pre = mem[pos].pre != NULL_PAGE ? &mem[ mem[pos].pre ] : (chunk*)(u32)-1;
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

extern u32 mem_start;
void inibuddy(multiboot_head_t *mboot_ptr){

    memset((u8*)mem, 0, sizeof(chunk)*MAX_PAGE);
    mem[0].pre = NULL_PAGE;
    mem[0].next = 1;
    mem[0].ini = 1;

    memory_map_t* mem;
    for(
        mem = (memory_map_t*)mboot_ptr->mmap_addr;
        (u32)mem < mboot_ptr->mmap_addr + mboot_ptr->mmap_length;
        mem = (memory_map_t*) ( (u32)mem + mem->size + sizeof(mem->size) )
       ){

        if(mem->type == 1 && mem->base_addr_low >= ENTRY_POINT ){

            if(mem->base_addr_low == ENTRY_POINT)
                addmem((u32)&mem_start , mem->base_addr_low + mem->length_low);
            else
                addmem(mem->base_addr_low, mem->base_addr_low + mem->length_low);
        }

    }
 
}
void listmem(){
    m_write("========list mem======\n",INFO);
    m_write("id           begin        pre          next         avai         size\n",INFO);

    u32 t_head = 0;
    //search
    while( t_head != NULL_PAGE && mem[t_head].ini != 0 ){
        chunk ch = mem[t_head];
        m_putint(t_head);
        m_write("   ",INFO);
        m_putint(ch.begin);
        m_write("   ",INFO);
        m_putint(ch.pre);
        m_write("   ",INFO);
        m_putint(ch.next);
        m_write("   ",INFO);
        m_putint(ch.avai);
        m_write("   ",INFO);
        m_putint(ch.size);
        m_write("\n",INFO);

        t_head = ch.next;
        
    }

}
