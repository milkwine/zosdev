cd kernel
make clean
make
cd ..

sudo losetup -o 32256 /dev/loop0 run/hard.img
sudo mount /dev/loop0 /mnt/hard

sudo cp kernel/kernel /mnt/hard
sudo cp run/initrd /mnt/hard

sudo umount /mnt/hard -l
sudo losetup -d /dev/loop0
