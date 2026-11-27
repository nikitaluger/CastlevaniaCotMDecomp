typedef struct {
    char pad0[0x2];
    u16 m2;
    char pad4[0x10];
    void *m14;
    char pad18[0xA];
    s16 m22;
    char pad24[0x48];
    s8 m6C;
} Rec_sub_080A53EC_arg0;

extern void sub_080A5418(void *);

void sub_080A53EC(void *arg0) {
    Rec_sub_080A53EC_arg0 *p = (Rec_sub_080A53EC_arg0 *)arg0;
    p->m6C = 0;
    p->m2 = (u16)(0x800 | p->m2);
    p->m14 = (void *)sub_080A5418;
    p->m22 = 1;
    ((void (*)(void *))p->m14)(arg0);
}
