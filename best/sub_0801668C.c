void sub_08011368(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

void sub_08017C38(void *arg0)
{
    s32 a = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *b = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *r4 = b + 0x34;
    u8 *r6 = b + 0x48;

    sub_08011368(a, r4, 5, 0);
    if (r4[0] & 2) {
        void **pp;
        *(u16 *)(r6 + 0x16) = 0;
        *(u16 *)(r6 + 0x18) = 0;
        ((u8 *)arg0)[*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19] = 0;
        pp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
    }
}

struct Node1668C {
    u8 *obj;
    struct Node1668C *next;
};

void sub_0801668C(void)
{
    struct Node1668C **base = (struct Node1668C **)0x020279D0;
    struct Node1668C *p = base[1];
    if (p != 0) {
        do {
            *(s32 *)(p->obj + 8) = 0;
            p = p->next;
        } while (p != 0);
    }
}
