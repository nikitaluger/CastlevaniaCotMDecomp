extern u8 D_02025358[];
extern u8 D_02025FF0[];
extern volatile u16 D_020274C8;
extern volatile u8 D_02025364;

void sub_0808CD00(void *arg0)
{
    u8 *p6C = *(u8 **)((u8 *)arg0 + 0x6C);
    u8 *r4 = p6C + 4;
    if (*(u16 *)r4 == 0) {
        u16 v = D_020274C8;
        if (v != 0) {
            if (D_02025364 == 0) {
                *(u16 *)r4 = v;
                D_020274C8 = 0;
                switch (v - 12) {
                  case 0: *(u16 *)(r4 + 2) = v; break;
                  case 1: *(u16 *)(r4 + 2) = v; break;
                  case 2: *(u16 *)(r4 + 2) = v; break;
                  case 3: *(u16 *)(r4 + 2) = v; break;
                  case 4: *(u16 *)(r4 + 2) = v; break;
                  case 5: *(u16 *)(r4 + 2) = v; break;
                  case 6: *(u16 *)(r4 + 2) = v; break;
                  case 7: *(u16 *)(r4 + 2) = v; break;
                  case 8: *(u16 *)(r4 + 2) = v; break;
                  case 9: *(u16 *)(r4 + 2) = v; break;
                  case 10: *(u16 *)(r4 + 2) = v; break;
                  case 11: *(u16 *)(r4 + 2) = v; break;
                }
            }
        }
    }
    switch (*(u16 *)r4 - 8) {
      case 0: D_020274C8 = 0; break;
      case 1: D_020274C8 = 0; break;
      case 2: D_020274C8 = 0; break;
      case 3: D_020274C8 = 0; break;
      case 4: D_020274C8 = 0; break;
      case 5: D_020274C8 = 0; break;
      case 6: D_020274C8 = 0; break;
    }
}
