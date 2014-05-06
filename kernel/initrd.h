#ifndef INITRD
#define INITRD 1
#include "multiboot.h"

void ini_initrd(multiboot_head_t *mboot_ptr);
void ls_initrd();
int read_initrd(int inode, u8* buf, int len, u32 pos);
void cat_initrd(int inode);

typedef struct ext2_superblock_t {
    u32 s_inodes_count;           //	 Total number of inodes in file system
    u32 s_blocks_count;           //	 Total number of blocks in file system
    u32 s_r_blocks_count;         //	 Number of blocks reserved for superuser (see offset 80)
    u32 s_free_blocks_count;      //	 Total number of unallocated blocks
    u32 s_free_inodes_count;      //	 Total number of unallocated inodes
    u32 s_first_data_block;       //	 Block number of the block containing the superblock
    u32 s_log_block_size;         //	log2 (block size) - 10. (In other words, the number to shift 1,02u32 to the left by to obtain the block size)
    u32 s_log_frag_size;          //	log2 (fragment size) - 10. (In other words, the number to shift 1,02u32 to the left by to obtain the fragment size)
    u32 s_blocks_per_group;       //	 Number of blocks in each block group
    u32 s_frags_per_group;        //	 Number of fragments in each block group
    u32 s_inodes_per_group;       //	 Number of inodes in each block group
    u32 s_mtime;                  //	 Last mount time (in POSIX time)
    u32 s_wtime;                  //	 Last written time (in POSIX time)
    u16 s_mnt_count;              //	 Number of times the volume has been mounted since its last consistency check (fsck)
    u16 s_max_mnt_count;          //	 Number of mounts allowed before a consistency check (fsck) must be done
    u16 s_magic;                  //	 Ext2 signature (0xef53), used to help confirm the presence of Ext2 on a volume
    u16 s_state;                  //	 File system state (see below)
    u16 s_errors;                 //	 What to do when an error is detected (see below)
    u16 s_minor_rev_level;        //	 Minor portion of version (combine with Major portion below to construct full version field)
    u32 s_lastcheck;              //	POSIX time of last consistency check (fsck)
    u32 s_checkinterval;          //	 Interval (in POSIX time) between forced consistency checks (fsck)
    u32 s_creator_os;             //	 Operating system ID from which the filesystem on this volume was created (see below)
    u32 s_rev_level;              //	 Major portion of version (combine with Minor portion above to construct full version field)
    u16 s_def_resuid;             //	 User ID that can use reserved blocks
    u16 s_def_resgid;             //	 Group ID that can use reserved blocks
} superblock_t;


/*
 * Structure of a blocks group descriptor
 */
typedef struct ext2_group_desc
{
    u32  bg_block_bitmap;        /* Blocks bitmap block */
    u32  bg_inode_bitmap;        /* Inodes bitmap block */
    u32  bg_inode_table;         /* Inodes table block */
    u16  bg_free_blocks_count;   /* Free blocks count */
    u16  bg_free_inodes_count;   /* Free inodes count */
    u16  bg_used_dirs_count;     /* Directories count */
    u16  bg_pad;
    u32  bg_reserved[3];
} groupdesc_t;

typedef struct ext2_inode_t {

    u16	i_mode;
    u16	i_uid;
    u32	i_size;
    u32	i_atime;
    u32	i_ctime;
    u32	i_mtime;
    u32	i_dtime;
    u16	i_gid;
    u16	i_links_count;
    u32	i_blocks;
    u32	i_flags;
    u32	i_osd1;
    u32	i_block[12];
    u32	i_sblock;
    u32	i_dblock;
    u32	i_tblock;
    u32	i_generation;
    u32	i_file_acl;
    u32	i_dir_acl;
    u32	i_faddr;
    u32	i_osd2_a;
    u32	i_osd2_b;
    u32	i_osd2_c;

} inode_t;
typedef struct ext2_directory_t {
  
    u32 inode;
    u16 rec_len;
    u8 name_len;
    u8 file_type;
    u8 name;        //char* str = (char*)&name

} directory_t;

#define EXT2_S_IFSOCK	0xC000	//socket
#define EXT2_S_IFLNK	0xA000	//symbolic link
#define EXT2_S_IFREG	0x8000	//regular file
#define EXT2_S_IFBLK	0x6000	//block device
#define EXT2_S_IFDIR	0x4000	//directory
#define EXT2_S_IFCHR	0x2000	//character device
#define EXT2_S_IFIFO	0x1000	//fifo

#define EXT2_S_IRUSR	0x0100	//user read
#define EXT2_S_IWUSR	0x0080	//user write
#define EXT2_S_IXUSR	0x0040	//user execute
#define EXT2_S_IRGRP	0x0020	//group read
#define EXT2_S_IWGRP	0x0010	//group write
#define EXT2_S_IXGRP	0x0008	//group execute
#define EXT2_S_IROTH	0x0004	//others read
#define EXT2_S_IWOTH	0x0002	//others write
#define EXT2_S_IXOTH	0x0001	//others execute

#endif
