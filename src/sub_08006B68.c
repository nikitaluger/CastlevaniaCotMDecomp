struct GlobalState {
    u8 _0[0x14B4];
    u32 unk14B4;
    u32 unk14B8;
    u8 _14BC[0x388];
    u32 status;          /* 0x1844 */
    u8 _1848[4];
    u32 proc184C;        /* 0x184C */
    u32 proc1850;        /* 0x1850 */
    u32 proc1854;        /* 0x1854 */
    u32 proc1858;        /* 0x1858 */
    u32 proc185C;        /* 0x185C */
    u32 proc1860;        /* 0x1860 */
    u32 proc1864;        /* 0x1864 */
    u32 proc1868;        /* 0x1868 */
    u32 proc186C;        /* 0x186C */
    u32 proc1870;        /* 0x1870 */
    u32 proc1874;        /* 0x1874 */
    u32 proc1878;        /* 0x1878 */
    u32 proc187C;        /* 0x187C */
    u32 proc1880;        /* 0x1880 */
    u32 proc1884;        /* 0x1884 */
    u32 proc1888;        /* 0x1888 */
    u8 _188C[8];
    u32 counter1894;     /* 0x1894 */
    u32 counter1898;     /* 0x1898 */
    u32 counter189C;     /* 0x189C */
    u32 counter18A0;     /* 0x18A0 */
};

struct Entity {
    u8 _0[0x14];
    void *unk14;
    u8 _18[0xA];
    s16 index22;         /* 0x22 */
    u8 _24[4];
};

void sub_08001738(u32);
void sub_08087970(void);
void sub_08087B50(void);
volatile int sub_080C31E4(void *, void *, s32);
extern struct GlobalState D_02025FF0;

/* Steps registered state processes based on status flags, updates counters, and performs a full reset sequence when all required flags are set. */
void sub_08006B68(void *arg0) {
    s32 v;

    if ((D_02025FF0.status & 0x40200000) == 0x200000) sub_08001738(D_02025FF0.proc184C);
    if (!(D_02025FF0.status & 0x20000000)) sub_08001738(D_02025FF0.proc1850);
    if (!(D_02025FF0.status & 0x10000000)) sub_08001738(D_02025FF0.proc1854);
    if (!(D_02025FF0.status & 0x08000000)) sub_08001738(D_02025FF0.proc1858);
    if (!(D_02025FF0.status & 0x04000000)) sub_08001738(D_02025FF0.proc185C);
    sub_08001738(D_02025FF0.proc1860);
    D_02025FF0.counter1894 += 1;
    if ((D_02025FF0.status & 0x41000000) == 0x40000000) sub_08001738(D_02025FF0.proc1864);
    if ((D_02025FF0.status & 0x00C00000) == 0x00400000) {
        sub_08001738(D_02025FF0.proc1868);
        v = D_02025FF0.counter1898 + 1;
        D_02025FF0.counter1898 = v;
        if (v > 1) D_02025FF0.status |= 0x00800000;
    }
    if ((D_02025FF0.status & 0x04400000) == 0x04000000) sub_08001738(D_02025FF0.proc186C);
    if ((D_02025FF0.status & 0x00600000) == 0x00400000) {
        sub_08001738(D_02025FF0.proc1870);
        v = D_02025FF0.counter189C + 1;
        D_02025FF0.counter189C = v;
        if (v > 1) D_02025FF0.status |= 0x00200000;
    }
    if ((D_02025FF0.status & 0x00420000) == 0x00400000) {
        sub_08001738(D_02025FF0.proc1880);
        v = D_02025FF0.counter18A0 + 1;
        D_02025FF0.counter18A0 = v;
        if (v > 1) D_02025FF0.status |= 0x00020000;
    }
    if (!(D_02025FF0.status & 0x00100000)) sub_08001738(D_02025FF0.proc1874);
    if (!(D_02025FF0.status & 0x00080000)) sub_08001738(D_02025FF0.proc1878);
    if (!(D_02025FF0.status & 0x00040000)) sub_08001738(D_02025FF0.proc187C);
    sub_08001738(D_02025FF0.proc1888);
    if (D_02025FF0.status == 0x7FFE0000) {
        D_02025FF0.status = 0;
        sub_08087970();
        sub_08087B50();
        D_02025FF0.unk14B8 = (D_02025FF0.unk14B4 & 0xF0) | 8;
        sub_08001738(D_02025FF0.proc184C);
        sub_08001738(D_02025FF0.proc185C);
        sub_08001738(D_02025FF0.proc1860);
        D_02025FF0.counter1894 += 1;
        sub_08001738(D_02025FF0.proc1864);
        D_02025FF0.unk14B4 = 0;
        D_02025FF0.unk14B8 = 0;
        *(u8 *)((u8 *)arg0 + ((struct Entity *)arg0)->index22 * 2 + 0x19) = 0;
        {
            s32 *fp = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *fp);
        }
    }
}
