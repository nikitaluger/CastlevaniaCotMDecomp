void sub_080BB984(void *, void *);
void sub_080BBA08(void *);
void sub_080BB940(void *, void *);
s32 sub_08098754(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Run one step of the entity's command script; command 0x78 clears the current
 * command byte and reloads the script from the default command table. */
void sub_080BA760(void *arg0) {
    u8 *obj = (u8 *)arg0;
    void *res = *(void **)(obj + 0x3C);
    sub_080BB984(res, (u8 *)res + 0x48);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0x78) {
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit;
            lit = (s32 *)0x08671BB0;
            sub_080C31E4(obj + 0x18, obj + 0x22, *lit);
        }
    }
}

void sub_080BA79C(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r0 = *(void **)(self + 0x3C);
    sub_080BB984(r0, (u8 *)r0 + 0x48);
    sub_080BBA08(arg0);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x18) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *nv;
            nv = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}

void sub_080BA7DA(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r4 = *(void **)(self + 0x4C);
    sub_080BB940(*(void **)(self + 0x3C), r4);
    if (sub_08098754(r4) != 0) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        {
            s32 *nv;
            nv = (s32 *)0x08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 0, *nv);
        }
    }
}

void sub_080BA644(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r0 = *(void **)(self + 0x3C);
    void *r4 = *(void **)(self + 0x4C);
    sub_080BB940(r0, r4);
    if (*(u8 *)((u8 *)r4 + 0x25) == 2) {
        *(s32 *)((u8 *)r0 + 0x68) = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *nv;
            nv = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}
