extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void advanceMotion(u8 *, s32);
extern void stepAnimationTrack(u8 *, u8 *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866FB08[];
struct S2A
{
  u8 flag;
};
void sub_080962C8(u8 *arg0)
{
  u8 *v38;
  u8 *p3C;
  u8 *p34;
  u8 *p48;
  s32 res;
  u8 *p2;
  u8 *pt;
  u8 *pt1;
  u8 *pb;
  u32 idx;
  u32 v1;
  u32 v2v;
  u32 b;
  u8 *base18;
  s32 idx2;
  u32 r2mask;
  u32 mask8000;
  u32 maskFFFF;
  v38 = *((u8 **) (arg0 + 0x38));
  p3C = *((u8 **) (arg0 + 0x3C));
  p34 = p3C + 0x34;
  p48 = p3C + 0x48;
  res = isOutsideCameraBounds(*((s32 *) (p3C + 8)), *((s32 *) (p3C + 0xC)));
  if (res == 1)
  {
    *((u8 *) ((*((u8 **) (p48 + 4))) + 1)) = 0;
    ((struct S2A *) (v38 + 0x2A))->flag &= 0xBF;
  }
  else
  {
    *((u8 *) ((*((u8 **) (p48 + 4))) + 1)) = 7;
    ((struct S2A *) (v38 + 0x2A))->flag |= 0x40;
  }
  *((u32 *) (arg0 + 0x14)) = (u32) D_0866FB08;
  *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) + 1;
  p2 = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
  *((u8 *) (p2 + 0x19)) = (*((u8 *) (p2 + 0x19))) + 1;
  idx2 = (*((s16 *) (arg0 + 0x22))) * 2;
  base18 = arg0;
  base18 += 0x18;
  b = *((u8 *) (((u32) base18) + ((u32) idx2)));
  sub_080C31E0((s32) arg0, *((u32 *) ((*((u32 *) (arg0 + 0x14))) + (b * 4))));
  *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) - 1;
  r2mask = (u16) ((*((u16 *) (arg0 + 2))) & 0x8000);
  if (r2mask == 0)
  {
    *((u16 *) ((*((u8 **) (p48 + 4))) + 4)) = *((u16 *) (p3C + 0x0A));
    *((u16 *) ((*((u8 * volatile *) (p48 + 4))) + 6)) = (*((u16 *) (p3C + 0x0E))) + 1;
    *((u32 *) (p48 + 8)) = *((u32 *) (p3C + 8));
    *((u32 *) (p48 + 0xC)) = *((u32 *) (p3C + 0xC));
    *((u16 *) (p48 + 0x10)) = (u16) r2mask;
    maskFFFF = 0xFFFF0000;
    advanceMotion(p3C, 0);
    if ((*((s16 *) (p48 + 0x12))) == 1)
    {
      stepAnimationTrack(v38, p34);
    }
    mask8000 = 0x8000;
    pt = gCameraState;
    pb = gMainWorkspace;
    pb += 0x18A8;
    idx = (((u32) (*pb)) + 1) * 0x40;
    pt1 = pt + 0x1278;
    v1 = *((u32 *) (pt1 + idx));
    *((u32 *) (v38 + 0x14)) = (*((u32 *) (p48 + 8))) - ((v1 + mask8000) & maskFFFF);
    idx = (((u32) (*pb)) + 1) * 0x40;
    pt += 0x127C;
    v2v = *((u32 *) (pt + idx));
    *((u32 *) (v38 + 0x18)) = (*((u32 *) (p48 + 0xC))) - ((v2v + 0xFFFF8000) & maskFFFF);
  }
}
