bximage <<END
hd
flat
20
hard.img
END
fdisk -c=dos -C40 -H16 -S63 hard.img <<END
n
p



a
1
w

END
losetup -o 32256 /dev/loop0 hard.img
mkfs.ext2 /dev/loop0
mount /dev/loop0 /mnt/hard/
mkdir -p /mnt/hard/boot/grub/
cp /usr/lib/grub/i386-pc/stage{1,2} /mnt/hard/boot/grub/
cp /usr/lib/grub/i386-pc/e2fs_stage1_5 /mnt/hard/boot/grub/
cp menu.lst /mnt/hard/boot/grub/
umount /mnt/hard/
losetup -d /dev/loop0
grub --no-floppy <<END
device (hd1) hard.img
geometry (hd1) 40 16 63
root (hd1,0)
setup (hd1)
quit
END
