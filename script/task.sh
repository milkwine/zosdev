cd task
make
cd ..
sudo mount run/initrd /mnt/intrd/
sudo cp task/ini /mnt/intrd/
sudo cp task/taska /mnt/intrd/
sudo umount -l /mnt/intrd/
