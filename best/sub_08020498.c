typedef struct {
    u8 pad[0x28];
    void * volatile f28;
} S98;

typedef struct {
    u8 pad[0x28];
    u16 f28;
} S0;

void sub_08020498(S0 *arg0, S98 *arg1) {
    u16 *src = (u16 *)0x080CE794;
    if ((u16)(arg0->f28 - 0x29) <= 9) {
        *(u8 *)((u8 *)arg1->f28 + 1) = 0;
    }
    *(u16 *)((u8 *)arg1->f28 + 6) = src[0];
    *(u16 *)((u8 *)arg1->f28 + 8) = src[1];
    *(u16 *)((u8 *)arg1->f28 + 0xA) = src[2];
    *(u16 *)((u8 *)arg1->f28 + 0xC) = src[3];
}
