extern u32 D_08670760[];
void sub_0800168C(void *a, u32 b, u32 c, u32 d);
void sub_080C31E0(void *a, u32 b);
void sub_080C31E8(void *a);

struct ArgBE { u8 _0[2]; u16 f2; u8 _1[0x10]; u32 f14; u8 _2[0x0A]; u16 f22; };

void sub_080BE23C(void *arg0)
{
    u32 *obj;
    u32 baseArr[2];
    u32 arrA[2];
    u32 arrB[2];
    u32 arrC[2];
    u32 i;
    u32 next;
    u32 j;
    u32 k;
    u32 idx;
    u32 sp28;

    sub_0800168C(arg0, 0, 0x0F8C, 0);
    obj = *(u32 **)((u8 *)arg0 + 0x3C);
    if (obj == NULL) {
        sub_080C31E0(arg0, *(u32 *)((u8 *)arg0 + 0x24));
        return;
    }
    obj[1] = 3;
    obj[2] = 1;

    for (i = 0; i < 4; i++) {
        next = i + 1;
        if (next == 4) next = 0;
        baseArr[0] = D_08670760[i];
        baseArr[1] = D_08670760[next];
        sp28 = (i * 3) << 8;
        for (j = 0; j < 0x40; j++) {
            u32 r4 = j * 2;
            for (k = 0; k < 2; k++) {
                u16 val = *(u16 *)(baseArr[k] + r4);
                arrA[k] = (u32)(val & 0x1F) << 16;
                arrB[k] = (u32)((val >> 5) & 0x1F) << 16;
                arrC[k] = (u32)((val >> 10) & 0x1F) << 16;
            }
            idx = j * 12 + sp28;
            obj[0x38C / 4 + idx / 4] = (arrA[1] - arrA[0]) >> 5;
            obj[0x390 / 4 + idx / 4] = (arrB[1] - arrB[0]) >> 5;
            obj[0x394 / 4 + idx / 4] = (arrC[1] - arrC[0]) >> 5;
        }
    }
    ((struct ArgBE *)arg0)->f2 |= 0x0800;
    ((struct ArgBE *)arg0)->f14 = 0x080BE388;
    ((struct ArgBE *)arg0)->f22 = 1;
    sub_080C31E8(arg0);
}
