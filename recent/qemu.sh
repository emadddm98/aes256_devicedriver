cd /home/emad/Desktop/qemu/
qemu-system-arm \
  -M versatilepb \
  -cpu arm1176 \
  -m 256 \
  -hda ~/2022-09-22-raspios-bullseye-armhf-lite.img \
  -net user,hostfwd=tcp::5022-:22 \
  -dtb /media/emad/C872-A3E8/qemu-rpi-kernel/versatile-pb-bullseye-5.10.63.dtb \
  -kernel /media/emad/C872-A3E8/qemu-rpi-kernel/kernel-qemu-5.10.63-bullseye \
  -append 'root=/dev/sda2 panic=1' \
  -no-reboot
