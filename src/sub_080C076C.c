void sub_080C082C(u32);
void sub_080C2F1C(u32 *, void *, u32);
void sub_080C0064(void);
void sub_080C1760(void);

/* Initializes the sound driver: resets the sound channels and sound DMA,
 * publishes the sound struct at 0x03007FF0, zero-fills it with CpuSet,
 * installs the callback table and finally marks the driver as ready. */
void sub_080C076C(void *arg0) {
    u32 zeroWord;
    *(u32*)arg0 = 0;
    *(vu16*)0x040000C6 = 0;
    *(vu16*)0x040000D2 = 0;
    *(vu16*)0x04000084 = 0x8F;
    *(vu16*)0x04000082 = 0xA90E;
    *(vu8*)0x04000089 = (*(vu8*)0x04000089 & 0x3F) | 0x40;
    *(vu32*)0x040000BC = (u32)arg0 + 0x350;
    *(vu32*)0x040000C0 = 0x040000A0;
    *(vu32*)0x040000C8 = (u32)arg0 + 0x980;
    *(vu32*)0x040000CC = 0x040000A4;
    *(vu32*)0x03007FF0 = (u32)arg0;
    zeroWord = 0;
    sub_080C2F1C(&zeroWord, arg0, 0x050003EC);
    *((u8*)arg0 + 6) = 8;
    *((u8*)arg0 + 7) = 0x0F;
    *(void**)((u8*)arg0 + 0x38) = (void*)0x080C0065;
    *(void**)((u8*)arg0 + 0x28) = (void*)0x080C1761;
    *(void**)((u8*)arg0 + 0x2C) = (void*)0x080C1761;
    *(void**)((u8*)arg0 + 0x30) = (void*)0x080C1761;
    *(void**)((u8*)arg0 + 0x3C) = (void*)0x080C1761;
    *(u32*)((u8*)arg0 + 0x34) = 0x0810C738;
    sub_080C082C(0x40000);
    *(u32*)arg0 = 0x68736D53;
}
