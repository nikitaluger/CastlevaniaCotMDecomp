extern u16 D_080CF990[];

void sub_0804BB7C(void *arg0, void *arg1) {
    u8 *outer = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 *p = D_080CF990;
    u16 v = *(u16 *)((u8 *)arg1 + 0x28);
    switch (v) {
    case 0x28:
        *(u8 *)(*(void * volatile *)(outer + 0x28) + 1) = 0;
        break;
    case 0x29:
        p += 4;
        break;
    }
    *(u16 *)((u8 *)*(void * volatile *)(outer + 0x28) + 6) = p[0];
    *(u16 *)((u8 *)*(void * volatile *)(outer + 0x28) + 8) = p[1];
    *(u16 *)((u8 *)*(void * volatile *)(outer + 0x28) + 0xA) = p[2];
    *(u16 *)((u8 *)*(void * volatile *)(outer + 0x28) + 0xC) = p[3];
}
