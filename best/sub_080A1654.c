extern s32 sub_08005820(s32 a);
extern s32 sub_0800583C(s32 a);
extern void sub_0808E348(s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
extern void sub_080C31E4(void *a, void *b, void *c);
extern u8 D_08671BB0[];
void sub_080A1654(void *arg0) {
    u8 *r6 = (u8 *)arg0;
    u8 *obj2 = *(u8 **)(r6 + 0x38);
    u8 *o3c = *(u8 **)(r6 + 0x3C);
    if ((*(u8 *)(r6 + *(s16 *)(r6 + 0x22) * 2 + 0x19) & 2) == 0) {
        u16 v = *(u16 *)obj2;
        *(u16 *)obj2 = (u16)((v & 0xFFF) | 0xE000);
    }
    { u32 r7 = 0;
      u8 *o2a = obj2 + 0x2A;
      u8 *q18 = r6;
      s32 offx = 0x22;
      u8 *q22 = r6 + offx;
      q18 = q18 + 0x18;
      do {
        s32 t5 = sub_0800583C(0x18000);
        sub_0808E348(*(s32 *)(o3c + 0x08), *(s32 *)(o3c + 0x0C) + (s32)0xFFE00000, t5, 0 - sub_08005820(0x50000), 0x16C1, (s32)(r7 & 1), 8);
        r7 += 1;
      } while (r7 <= 0x1F);
      *(u8 *)o2a = (u8)(*o2a & 0xBF);
      *(u8 *)(r6 + *(s16 *)(r6 + 0x22) * 2 + 0x19) = 0;
      sub_080C31E4(q18, q22, (void *)*(u32 *)D_08671BB0);
    }
}
