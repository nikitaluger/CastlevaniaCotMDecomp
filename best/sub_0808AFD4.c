s32 sub_0800168C(void *, s32, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;

void sub_0808AFD4(void *arg0)
{
    if (sub_0800168C(arg0, 0, 0x3C, 3) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    {
        s16 idx = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[idx * 2 + 0x19] = 0;
        {
            void **lit = &D_08671BB0;
            u8 *base = (u8 *)arg0 + 0x18;
            sub_080C31E4(base, (u8 *)arg0 + 0x22, *lit);

            idx = *(s16 *)((u8 *)arg0 + 0x22);
            ((u8 *)arg0)[idx * 2 + 0x19]++;

            idx = *(s16 *)((u8 *)arg0 + 0x22);
            base = base + idx * 2;
            sub_080C31E0(arg0, *(void **)(*(u8 **)((u8 *)arg0 + 0x14) + base[0] * 4));
        }
    }
}
