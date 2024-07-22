cd /home/emad/Desktop/qemu/
qemu-system-aarch64 -boot d -cdrom ../2023-12-05-raspios-bookworm-arm64.img -cpu cortex-a72 -m 1G -M raspi3b -serial stdio -hda /media/emad/1280-51BA/raspbian/mydisk.img -nic user,hostfwd=tcp::5022-:22 -no-reboot
