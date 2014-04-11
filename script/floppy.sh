dd if=/dev/zero of=floppy.img bs=512 count=2880
losetup /dev/loop0 floppy.img 
mkfs.msdos /dev/loop0
mount /dev/loop0 /mnt/floppy/
mkdir -p /mnt/floppy/boot/grub/
cp /usr/lib/grub/i386-pc/stage{1,2} /mnt/floppy/boot/grub/
cp /usr/lib/grub/i386-pc/fat_stage1_5 /mnt/floppy/boot/grub/
#cat grub|grub
#sudo umount -l /dev/loop0
#sudo losetup -d /dev/loop0 
