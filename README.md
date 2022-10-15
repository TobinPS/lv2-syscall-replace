# LV2 Syscall replace sample

This sample is written for Rebug 4.84.1 DECR edition, so you will need to update the offsets in init.c for your given firmware.

This code shows replacing syscall 119. You can also call `lv1_get_rtc` if you wish, however then it seems to behave the same as the original syscall and wouldn't demonstrate much.

This code was written by referencing COBRA, and all credits should go to them, this is just a more concise sample of replacing a syscall. You can run this payload with the webman mod kernel payloads web interface, or using COBRA syscalls.
