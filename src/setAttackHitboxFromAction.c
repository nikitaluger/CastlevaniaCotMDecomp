extern u16 D_080CFD80[];
extern u16 D_080CFD88[];
extern u16 D_080CFD90[];
extern u16 D_080CFD98[];
extern u16 D_080CFDA0[];
extern u16 D_080CFDA8[];
extern u16 D_080CFDB0[];
extern u16 D_080CFDB8[];
extern u16 D_080CFDC0[];
struct HitboxTarget
{
  u8 pad[0x28];
  u8 * volatile hitbox;
};
/* Select an attack hitbox by the source's action index and copy its four
 * 16-bit box edges into the target's hitbox. */
void setAttackHitboxFromAction(void *arg0, void *arg1)
{
  u8 *src = arg0;
  u8 *dst = arg1;
  u16 *boxParams = D_080CFD80;
  u32 rangeCheck;
  rangeCheck = (u16) ((*((u16 *) (src + 0x28))) - 7);
  if (rangeCheck <= 6)
  {
    boxParams += 8;
  }
  switch ((*((u16 *) (src + 0x28))) - 4)
  {
    case 0:
      boxParams = D_080CFD88;
      break;

    case 5:
      boxParams = D_080CFDC0;
      break;

    case 6:
      boxParams = D_080CFDB8;
      break;

    case 7:
      boxParams = D_080CFD98;
      break;

    case 11:
      boxParams = D_080CFDA0;
      break;

    case 13:
      boxParams = D_080CFDA8;
      break;

    case 14:
      boxParams = D_080CFDB0;
      break;

    case 16:
      boxParams = D_080CFDB0;
      break;

    case 18:
      boxParams = D_080CFD90;
      break;

    default:
      break;

  }

  *((u16 *) (((struct HitboxTarget *) dst)->hitbox + 6)) = boxParams[0];
  *((u16 *) (((struct HitboxTarget *) dst)->hitbox + 8)) = boxParams[1];
  *((u16 *) (((struct HitboxTarget *) dst)->hitbox + 10)) = boxParams[2];
  *((u16 *) (((struct HitboxTarget *) dst)->hitbox + 12)) = boxParams[3];
}
