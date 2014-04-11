cd kernel
make clean
make
cd ..
sudo mount run/floppy.img /mnt/floppy
sudo cp kernel/kernel /mnt/floppy
sudo umount /mnt/floppy -l
