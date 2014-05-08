#include "initrd.h"
#include "common.h"
#include "buddy.h"

#define block2addr(b) (b * s_block + i_start)
static u32 i_start;
static u32 i_end;
static groupdesc_t* groups;
static int c_group;
static int s_block;
static superblock_t* superblock;

static inode_t* find_inode(int inode){

    if(inode<=0){
        m_printf("inode %d error",inode);
        return 0;
    }
    int g = inode / superblock->s_inodes_per_group;
    g = inode % superblock->s_inodes_per_group != 0 ? g+1 : g;
    g--;
    inode_t* inodes =(inode_t*)block2addr((u32)groups[g].bg_inode_table);
    inodes+=inode-1;
    if(inodes->i_size==0){
        m_printf("inode %d not exists\n",inode);
        return 0;
    }
    return inodes;

}
u32 load_initrd(int inode,int* p_size){
    
    inode_t* inodes = find_inode(inode);
    if((u32)inodes == 0)return 0;
    u16 mode = inodes->i_mode;
    if(!(mode & EXT2_S_IFREG)){
        m_printf("inode %d is not a regular file\n",inode);
        return 0;
    }
    *p_size = inodes->i_size;
    int c_page = inodes->i_size / PAGE_SIZE;
    c_page = inodes->i_size % PAGE_SIZE ? c_page+1 : c_page;
    int base = k_malloc(c_page);
    if(base == -1){
        m_printf("do not have enoght memory\n");
        return 0;
    }

    char* buf = (char*)base;
    //only deal with 12 direct blocks;Singly&Doubly&Triply do not support
    int i; u32 size = 0; char* ch = 0;
    for (i = 0; i < 12 && size < inodes->i_size;) {
        if(ch==0 || size % s_block == 0){
            ch = (char*)block2addr( inodes->i_block[i] );
            i++;
        }
        buf[size++] = *ch++;
    }
    return (u32)base;
}
static void print_inode(int inode){

    inode_t* inodes = find_inode(inode);
    if((u32)inodes == 0)return;

    u16 mode = inodes->i_mode;
    m_printf(mode & EXT2_S_IFDIR ? "d" : "-");
    m_printf(mode & EXT2_S_IRUSR ? "r" : "-");
    m_printf(mode & EXT2_S_IWUSR ? "w" : "-");
    m_printf(mode & EXT2_S_IXUSR ? "x" : "-");
    m_printf(mode & EXT2_S_IRGRP ? "r" : "-");
    m_printf(mode & EXT2_S_IWGRP ? "w" : "-");
    m_printf(mode & EXT2_S_IXGRP ? "x" : "-");
    m_printf(mode & EXT2_S_IROTH ? "r" : "-");
    m_printf(mode & EXT2_S_IWOTH ? "w" : "-");
    m_printf(mode & EXT2_S_IXOTH ? "x" : "-");
    m_printf(" %d ",inode);
    m_printf(" %d ",inodes->i_size);


}
void cat_initrd(int inode){

    inode_t* inodes = find_inode(inode);
    if((u32)inodes == 0)return;
    u16 mode = inodes->i_mode;
    if(!(mode & EXT2_S_IFREG)){
        m_printf("inode %d is not a regular file\n",inode);
        return;
    }
    //only deal with 12 direct blocks;Singly&Doubly&Triply do not support
    int i; u32 size = 0; char* ch = 0;
    for (i = 0; i < 12 && size < inodes->i_size;) {
        if(ch==0 || size % s_block == 0){
            ch = (char*)block2addr( inodes->i_block[i] );
            i++;
        }
        m_putchar(*ch++);
        size++;
    }
}
int read_initrd(int inode, u8* buf, int len, u32 pos){
    
    inode_t* inodes = find_inode(inode);
    if((u32)inodes == 0)return -1;
    u16 mode = inodes->i_mode;
    if(!(mode & EXT2_S_IFREG)){
        m_printf("inode %d is not a regular file\n",inode);
        return;
    }
    //only deal with 12 direct blocks;Singly&Doubly&Triply do not support
    int size = 0;
    int i = pos / s_block;
    u8* ch = (u8*)block2addr( inodes->i_block[i] ) + pos % s_block;
    while( i<12 && size < len && pos < inodes->i_size ){

        if(pos % s_block == 0){
            ch = (char*)block2addr( inodes->i_block[i] );
            i++;
        }
        buf[size++] = *ch++;
        pos++;
    }
    return size;
}
void ls_initrd(){

    int inode = 2;
    int g = 0;

    inode_t* inodes =(inode_t*)block2addr((u32)groups[g].bg_inode_table);
    inodes+=inode-1;

    if(! inodes->i_mode & EXT2_S_IFDIR){
        m_printf("inode %d is not a directory\n",inode);
        return;
    }

    //only deal with first inode block entries
    int c = 0;
    u32 addr = block2addr( (u32)inodes->i_block[0] );
    while(addr < block2addr( (u32)inodes->i_block[0] )+s_block){
        directory_t* dir = (directory_t*)addr;
        char* name = (char*)&dir->name;
        name[dir->name_len]='\0';
        if( dir->file_type == 1 || dir->file_type == 2){    //regular file & directory file

            print_inode( dir->inode );
            m_printf("(%d)%s\n",dir->inode,name);
            c++;
        }
        addr+=dir->rec_len;
    }
    m_printf("count:%d\n",c);
    

}

void ini_initrd(multiboot_head_t *mboot_ptr){
    if(mboot_ptr->mods_count == 0){
        //TODO panic
    }

    multiboot_module_t* mod = (multiboot_module_t*)mboot_ptr->mods_addr;
    m_printf("start:%x  end:%x\n",mod->mod_start,mod->mod_end);
    i_start = mod->mod_start;
    i_end = mod->mod_end;
    superblock = (superblock_t*)(i_start+1024);
    m_printf("inodes:%d blocks:%d magic:%x\n",superblock->s_inodes_count,superblock->s_blocks_count,superblock->s_magic);
    if(superblock->s_magic != 0xef53){
        //TODO panic
    }
    c_group = superblock->s_blocks_count/superblock->s_blocks_per_group;
    c_group =  superblock->s_blocks_count % superblock->s_blocks_per_group != 0 ? c_group+1 : c_group;
    s_block = 1024 << superblock->s_log_block_size;
    m_printf("groups: %d block size:%d\n",c_group,s_block);
    if(s_block == 1024)
        groups = (groupdesc_t*)(2048+i_start);    
    else
        groups = (groupdesc_t*)(s_block+i_start);    
    int i;
    for (i = 0; i < c_group; i++) {
        m_printf("group %d inode table:%x\n",i,groups[i].bg_inode_table);
    }
}
