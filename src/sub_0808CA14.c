void sub_08006588(s32, s32, s32);
void sub_08006858(s32, s32, s32);
void sub_08006888(s32, s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 _0[0x1848]; u32 f1848; u8 _1[0x18C5 - 0x184C]; u8 f18C5; u8 f18C6; };
extern struct S_02025FF0 D_02025FF0;

struct Dma3 { vu32 src, dst, ctrl; };
#define REG_DMA3 (*(volatile struct Dma3 *)0x040000D4)

extern s32 D_08671BB0;

/* Trigger a one-shot visual effect: set up the graphics layers and DMA the
 * effect gfx into its buffer, mark the global state flags, clear then bump the
 * acting child's flag around spawning the effect, and finally invoke the
 * entity's callback through the child index table. */
void sub_0808CA14(u8 *self) {
    u8 *childPtr;
    u32 childAddr;
    sub_08006588(0xF, 0xF, 0);
    REG_DMA3.src = 0x085D3CC4;
    REG_DMA3.dst = 0x02022C44;
    REG_DMA3.ctrl = 0x80000010;
    (void)REG_DMA3.ctrl;
    sub_08006858(0xF, 0xF, (s32)0xFFFF0000);
    sub_08006888(0xF, 0xF, 0x80 << 0x11);
    D_02025FF0.f1848 |= 0x4DBE0000;
    D_02025FF0.f18C6 = 1;
    D_02025FF0.f18C5 = 1;
    *(u8 *)(self + (s16)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        void **effectTable = (void **)&D_08671BB0;
        childPtr = self + 0x18;
        sub_080C31E4(childPtr, self + 0x22, (s32)*effectTable);
    }
    childAddr = (s16)*(s16 *)(self + 0x22);
    childAddr <<= 1;
    childAddr += (u32)self;
    ((u8 *)childAddr)[0x19] = ((u8 *)childAddr)[0x19] + 1;
    childPtr += (s16)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *childPtr * 4));
}
