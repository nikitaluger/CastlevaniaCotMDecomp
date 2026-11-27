extern s32 sub_080C31E0(s32, s32);
extern u32 gTrigFuncPtr;

/* Rotates a child offset about an entity's origin using the sine lookup held
 * in gTrigFuncPtr, writing the resulting X/Y coordinates to outX/outY. */
void sub_08027A4C(u8 *entity, s32 angle, s32 *outX, s32 *outY)
{
  s32 quarterTurn;
  u32 sinFnAddr;
  s32 sinPart;
  s32 cosVal;
  s32 sinVal;
  s32 cosPart;
  u8 *motion;
  u8 *ext;
  s32 baseX;
  s32 baseY;
  s32 cosB;
  s32 angleLo;

  motion = *((u8 **) (entity + 0x3C));
  ext = motion + 0x48;
  angleLo = angle & 0xFFFF;
  sinFnAddr = (u32) (&gTrigFuncPtr);
  quarterTurn = 0x4000;
  cosVal = sub_080C31E0(angleLo + quarterTurn, *((s32 *) sinFnAddr));
  if (cosVal < 0)
  {
    cosVal += 0x7FF;
  }
  cosPart = cosVal >> 11;
  sinVal = sub_080C31E0(angleLo, *((s32 *) sinFnAddr));
  if (sinVal < 0)
  {
    if (1)
    {
      sinVal += 0xFFF;
    }
  }
  sinPart = sinVal >> 12;
  baseX = (sub_080C31E0((*((u16 *) ((*((u8 **) (ext + 0x58))) + 4))) + quarterTurn, *((s32 *) sinFnAddr)) * 8) + (*((s32 *) (motion + 0x48)));
  baseY = (sub_080C31E0(*((u16 *) ((*((u8 **) (ext + 0x58))) + 4)), *((s32 *) sinFnAddr)) * 8) + (*((s32 *) (ext + 4)));
  cosB = sub_080C31E0((*((u16 *) ((*((u8 **) (ext + 0x58))) + 2))) + quarterTurn, *((s32 *) sinFnAddr));
  *outX = ((cosPart * cosB) - (sinPart * sub_080C31E0(*((u16 *) ((*((u8 **) (ext + 0x58))) + 2)), *((s32 *) sinFnAddr)))) + baseX;
  ;
  *outY = ((cosPart * sub_080C31E0(*((u16 *) ((*((u8 **) (ext + 0x58))) + 2)), *((s32 *) sinFnAddr))) + (sinPart * sub_080C31E0((*((u16 *) ((*((u8 **) (ext + 0x58))) + 2))) + quarterTurn, *((s32 *) sinFnAddr)))) + baseY;
}
