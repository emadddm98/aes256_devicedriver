cd /home/emad/Desktop/qemu/
qemu-system-arm -kernel /media/emad/1280-51BA/copy/kernel-qemu-jessie -cpu arm1176 -m 256 -M versatilepb -serial stdio -append "root=/dev/sda2 rootfstype=ext4 rw" -hda /media/emad/1280-51BA/copy/2017-04-10-raspbian-jessie.img -no-reboot -netdev tap, id=foo, ifname=tap0 -device virtio-net-pci, netdev=foo -nic id=user0, net= 
