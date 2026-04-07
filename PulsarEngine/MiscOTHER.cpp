#include <kamek.hpp>
#include <RuntimeWrite.hpp>
#include <Settings/Settings.hpp>
#include <PulsarSystem.hpp>
#include <MarioKartWii/UI/Section/SectionMgr.hpp>

namespace Pulsar {
namespace Race {
	
//Itembox From Common [Gabriela_]
asmFunc ItemBoxCommon() {
    ASM(
   nofralloc;
   li        r4, 0x1;
   lis       r12, 0x6974;
   ori       r12, r12, 0x656D;
   lwz       r11, 0x0(r5);
   cmplw     r11, r12;
   bne-      loc_0x1C;
   li        r4, 0;

   loc_0x1C:
   blr;)
}
kmCall(0x8081FDAC, ItemBoxCommon);

//RACE SPECIFIC

//Fix Mushroom Glitch
kmWrite8(0x807BA077, 0x00000000);

//Impervious TC
kmWrite32(0x807AFAA8, 0x48000038);

//Rexcore Countdown (Look Behind)
kmWrite32(0x805A225C, 0x38800001);

//Extend race online
kmWrite32(0x8053F3B8,0x3C600005);
kmWrite32(0x8053F3BC,0x38837E40);
kmWrite32(0x8053F478,0x4800000C); //6 Minute DC Disables

//Anti Online Penalized by B_squo
kmWrite32(0x80549218, 0x38600000);
kmWrite32(0x8054921c, 0x4e800020);

//WW Bubble Skip [Ro]
kmWrite8(0x80609647, 0x0000003C);
kmWrite8(0x8060964F, 0x0000001E);

//Remove Chadderz Button
kmWrite16(0x8064B982, 0x00000005);
kmWrite32(0x8064BA10, 0x60000000);
kmWrite32(0x8064BA38, 0x60000000);
kmWrite32(0x8064BA50, 0x60000000);
kmWrite32(0x8064BA5C, 0x60000000);
kmWrite16(0x8064BC12, 0x00000001);
kmWrite16(0x8064BC3E, 0x00000484);
kmWrite16(0x8064BC4E, 0x000010D7);
kmWrite16(0x8064BCB6, 0x00000484);
kmWrite16(0x8064BCC2, 0x000010D7);

//Floating Flibs [Stealth Steeler]
//kmWrite32(0x808a5770, 0x00000000);
//kmWrite32(0x808a5774, 0x00000000);

//No Bullet Bill Cancel When Touching Bottom of Rainbow Road [Ro]
kmWrite32(0x8059BE30, 0x60000000);

//Skip Mode Selection Online [Ro]
kmWrite32(0x8064be64, 0x3800008F); //Regional/CTWW -> VS Race
kmWrite32(0x80609aac, 0x3800008B); //Back from Character Selection

//Fix these fuckin boxes [Unnamed]
asmFunc ItemRespawn() {
loc_0x0:
  li r12, 0x30 //30 frames
  stw r12, 184(r27)
  stw r0, 176(r27)

}
kmCall(0x80828EDC, ItemRespawn);

//Worldwide/Regional Opponent Zoom in Regional/Worldwide
kmWrite32(0x805E527C, 0x3BC00000);

//CODES BELOW WERE TAKEN FROM INSANE KART WII!

//Event Overflow Protection [Seeky]
asmFunc EventOverflowProtection() {
  ASM(
    nofralloc;
  lbz       r12, 0x1C(r27);
  add       r12, r30, r12;
  cmpwi     r12, 0xE0;
  blt+      loc_0x18;
  li        r0, 0;
  stb       r0, 0x19(r27);

loc_0x18:
  lbz       r0, 0x19(r27);
  blr;
  )
}
kmCall(0x8065BBD4, EventOverflowProtection);

//Enhanced Pause Menu [Ro]
kmWrite32(0x8062c658, 0x38800019);
kmWrite32(0x8062c79c, 0x38800019);
kmWrite32(0x80633a98, 0x38600019);
kmWrite32(0x8062c8e0, 0x38800019);
kmWrite32(0x80633970, 0x38600019);
kmWrite32(0x8083d618, 0x60000000);

extern "C" void sInstance__8Racedata(void*);
extern "C" void sInstance__10SectionMgr(void*);
asmFunc EnhancedPauseMenu1() {
  ASM(
  lwz r3, sInstance__10SectionMgr@l (r6);
  lwz r12, sInstance__8Racedata@l (r6);
  lwz r0, 0x1760 (r12);
  cmpwi r0, 2;
  beq end;

  cmpwi r4, 0x49;
  beq decreaseRaceNum;

  cmpwi r4, 0x4A;
  bne end;

  li r4, 0x4B;

  cmpwi r0, 1;
  beq decreaseRaceNum;

  li r4, 0x4C;

  decreaseRaceNum:
  lwz r6, 0x98 (r3);
  lwz r31, 0x60 (r6);
  subi r31, r31, 1;
  stw r31, 0x60 (r6);

  li r31, 5;
  stw r31, 0x1764 (r12);

  end:
  mr r31, r5;
  blr;
  )
}
kmCall(0x806024d8, EnhancedPauseMenu1);

extern "C" void sInstance__8Racedata(void*);
asmFunc EnhancedPauseMenu2() {
  ASM(
  lis r3, sInstance__8Racedata@ha;
  lwz r3, sInstance__8Racedata@l (r3);
  lwz r4, 0x1760 (r3);
  cmpwi r4, 2;
  beq end;
  li r4, 0x1;
  stw r4, 0xD18 (r3);
  stw r4, 0xE08 (r3);
  stw r4, 0xEF8 (r3);

  end:
  li        r3, 0x6C4;
  blr;
  )
}
kmCall(0x80623df4, EnhancedPauseMenu2);

kmWrite32(0x80859068, 0x48000808);
kmWrite32(0x80858e38, 0x48000040);

//Goomba Size Memorizer [_tZ]
kmWrite32(0x80821E78, 0x38600158);
kmWrite32(0x806DC750, 0xD19D0044);
kmWrite32(0x806DC6F0, 0xD19D0044);
kmWrite32(0x806DCB30, 0xD19C0044);
kmWrite32(0x806DCAD4, 0xD19C0040);

asmFunc GoombaSizeMemorizer1() {
    ASM(
        nofralloc;
  lfs       f8, 0x3C(r29);
  lfs       f7, 0x40(r29);
  lfs       f6, 0x44(r29);
  stfs      f8, 0x14C(r29);
  stfs      f7, 0x150(r29);
  stfs      f6, 0x154(r29);
  li        r30, 0;
  blr;

    )
}
kmCall(0x806db1b4, GoombaSizeMemorizer1);

asmFunc GoombaSizeMemorizer2() {
    ASM(
        nofralloc;
  lfs       f9, 0x14C(r29);
  lfs       f10, 0x150(r29);
  lfs       f11, 0x154(r29);
  fmul      f12, f11, f1;
  fmul      f1, f9, f1;
  fmul      f0, f10, f0;
  stfs      f1, 0x3C(r29);
  blr;

    )
}
kmCall(0x806DC6E8, GoombaSizeMemorizer2);
kmCall(0x806DC748, GoombaSizeMemorizer2);

asmFunc GoombaSizeMemorizer3() {
    ASM(
        nofralloc;
  lfs       f9, 0x14C(r28);
  lfs       f10, 0x150(r28);
  lfs       f11, 0x154(r28);
  fmul      f12, f11, f1;
  fmul      f1, f9, f1;
  fmul      f0, f10, f0;
  stfs      f1, 0x3C(r28);
  blr;

    )
}
kmCall(0x806DCB28, GoombaSizeMemorizer3);

asmFunc GoombaSizeMemorizer4() {
    ASM(
        nofralloc;
  lfs       f9, 0x14C(r28);
  lfs       f10, 0x150(r28);
  lfs       f11, 0x154(r28);
  fmul      f12, f11, f0;
  fmul      f13, f9, f0;
  fmul      f0, f10, f0;
  stfs      f12, 0x3C(r28);
  blr;

    )
}
kmCall(0x806DCACC, GoombaSizeMemorizer4);

//Poocha Fix [Ro]
asmFunc PochaFix() {
    ASM(
        nofralloc;
  lbz       r31, 0x78(r3);
  cmpwi     r31, 0;
  beq-      loc_0x24;
  lbz       r31, 0xE(r3);
  addi      r31, r31, 0x1;
  cmpwi     r31, 0x3C;
  blt-      loc_0x24;
  li        r31, 0;
  stb       r31, 0x78(r3);

loc_0x24:
  stb       r31, 0xE(r3);
  mr        r31, r3;
  blr;

    )
}
kmCall(0x8069B3A8, PochaFix);

extern "C" void sInstance__Q24Item7Manager(void*);
asmFunc ItemsOnMinimap1() {
  ASM(
    nofralloc;
  lis       r3, sInstance__Q24Item7Manager@ha;
  lwz       r3, sInstance__Q24Item7Manager@l(r3);
  lwz       r4, 0x244(r3);
  lwz       r4, 0x0(r4);
  lhz       r4, 0x8(r4);
  lwz       r3, 0x248(r3);
  add       r3, r4, r3;
  mulli     r3, r3, 0x1B4;
  addi      r3, r3, 0x1A4;
  blr;
  )
}

asmFunc ItemsOnMinimap2() {
  ASM(
    nofralloc;
  addi      r26, r27, 0x1;
  lis       r5, sInstance__Q24Item7Manager@ha;
  lwz       r5, sInstance__Q24Item7Manager@l(r5);
  lwz       r6, 0x244(r5);
  lwz       r6, 0x0(r6);
  lhz       r6, 0x8(r6);
  lwz       r5, 0x248(r5);
  add       r5, r6, r5;
  add       r26, r26, r5;
  blr;
  )
}

extern "C" void ItemsOnMinimapEnd3(void*);
extern "C" void __ct__15LayoutUIControlFv(void*);
extern "C" void ItemsOnMinimapSymbol1(void*);
extern "C" void AddControl__9UIControlFUiP9UIControl(void*);
extern "C" void ItemsOnMinimapSymbol2(void*);
extern "C" void ItemsOnMinimapSymbol3(void*);
extern "C" void ItemsOnMinimapSymbol4(void*);
extern "C" void Load__13ControlLoaderFPCcPCcPCcPPCc(void*);
extern "C" void ItemsOnMinimapSymbol5(void*);
extern "C" void ItemsOnMinimapSymbol6(void*);
extern "C" void ItemsOnMinimapSymbol7(void*);
extern "C" void ItemsOnMinimapSymbol9(void*);
extern "C" void SetPicturePane__15LayoutUIControlFPCcPCc(void*);
asmFunc ItemsOnMinimap3() {
  ASM(
    nofralloc;
  bctrl;
  li        r26, 0;
  addi      r23, r24, 0x1A4;

loc_0xC:
  li        r25, 0;

loc_0x10:
  mr        r3, r23;
  lis       r12, __ct__15LayoutUIControlFv@h;
  ori       r12, r12, __ct__15LayoutUIControlFv@l;
  mtctr     r12;
  bctrl;     
  lis       r3, ItemsOnMinimapSymbol1@h;
  ori       r3, r3, ItemsOnMinimapSymbol1@l;
  stw       r3, 0x0(r23);
  mr        r3, r24;
  addi      r28, r28, 0x1;
  mr        r4, r28;
  mr        r5, r23;
  lis       r12, AddControl__9UIControlFUiP9UIControl@h;
  ori       r12, r12, AddControl__9UIControlFUiP9UIControl@l;
  mtctr     r12;
  bctrl;     
  addi      r3, r1, 0x20;
  stw       r23, 0x0(r3);
  lis       r6, ItemsOnMinimapSymbol2@h;
  ori       r4, r6, ItemsOnMinimapSymbol2@l;
  ori       r5, r6, ItemsOnMinimapSymbol3@l;
  ori       r6, r6, ItemsOnMinimapSymbol4@l;
  li        r7, 0;
  lis       r12, Load__13ControlLoaderFPCcPCcPCcPPCc@h;
  ori       r12, r12, Load__13ControlLoaderFPCcPCcPCcPPCc@l;
  mtctr     r12;
  bctrl;     
  mr        r3, r23;
  lis       r5, ItemsOnMinimapSymbol2@h;
  ori       r4, r5, ItemsOnMinimapSymbol2@l;
  ori       r5, r5, ItemsOnMinimapSymbol5@l;
  lis       r12, ItemsOnMinimapSymbol6@h;
  ori       r12, r12, ItemsOnMinimapSymbol6@l;
  mtctr     r12;
  bctrl;     
  stb       r26, 0x81(r23);
  stb       r25, 0x82(r23);
  lis       r6, ItemsOnMinimapSymbol7@h;
  ori       r3, r6, ItemsOnMinimapSymbol7@l;
  bl        loc_0xC0;
  opword    0x000c182c;
  opword    0x604c5820;
  opword    0x7840848c;
  opword    0x689c9000;

loc_0xC0:
  mflr      r4;
  lbzx      r4, r4, r26;
  add       r5, r3, r4;
  mr        r3, r23;
  ori       r4, r6, ItemsOnMinimapSymbol9@l;
  lis       r12, SetPicturePane__15LayoutUIControlFPCcPCc@h;
  ori       r12, r12, SetPicturePane__15LayoutUIControlFPCcPCc@l;
  mtctr     r12;
  bctrl;     
  addi      r23, r23, 0x1B4;
  addi      r25, r25, 0x1;
  lis       r3, sInstance__Q24Item7Manager@ha;
  lwz       r3, sInstance__Q24Item7Manager@l(r3);
  mulli     r4, r26, 0x24;
  add       r3, r3, r4;
  lwz       r3, 0x50(r3);
  cmpw      r25, r3;
  blt+      loc_0x10;
  addi      r26, r26, 0x1;
  cmpwi     r26, 0xF;
  blt+      loc_0xC;
  b ItemsOnMinimapEnd3;
  )
}

extern "C" void ItemsOnMinimapEnd4(void*);
asmFunc ItemsOnMinimap4() {
  ASM(
    nofralloc;
  bctrl;     
  lwz       r3, 0x16C(r31);
  cmpwi     r3, 0;
  beq-      loc_0x84;
  lwz       r3, 0x198(r31);
  li        r4, 0xA0;
  stb       r4, 0xB8(r3);
  lis       r4, 0x4140;
  stw       r4, 0x4C(r3);
  stw       r4, 0x50(r3);
  li        r3, 0x1;
  stb       r3, 0x80(r31);
  lis       r3, sInstance__Q24Item7Manager@ha;
  lwz       r3, sInstance__Q24Item7Manager@l(r3);
  lbz       r4, 0x81(r31);
  mulli     r4, r4, 0x24;
  add       r3, r3, r4;
  lwz       r4, 0x58(r3);
  lbz       r5, 0x81(r31);
  cmpwi     r5, 0x7;
  beq-      loc_0x84;
  lbz       r5, 0x82(r31);
  cmpw      r5, r4;
  bge-      loc_0x84;
  li        r4, 0;
  stb       r4, 0x80(r31);
  lwz       r3, 0x4C(r3);
  rlwinm    r4,r5,2,0,29;
  lwzx      r3, r3, r4;
  addi      r4, r3, 0x44;
  lswi      r5, r4, 0xC;
  addi      r4, r31, 0x19C;
  stswi     r5, r4, 0xC;

loc_0x84:
  b ItemsOnMinimapEnd4;
  )
}
kmCall(0x80858194, ItemsOnMinimap1);
kmCall(0x807ea450, ItemsOnMinimap2);
kmBranch(0x807ea6e0, ItemsOnMinimap3);
kmBranch(0x807eaca8, ItemsOnMinimap4);


//Force Language Files to English [Toadette Hack Fan]
kmRegionWrite8(0x8088FDC5, 0x55, 'P');
kmRegionWrite8(0x8088FDCD, 0x55, 'P');
kmRegionWrite8(0x8088FDD5, 0x55, 'P');
kmRegionWrite8(0x8088FDDD, 0x55, 'P');
kmRegionWrite8(0x8088FDE5, 0x55, 'P');
kmRegionWrite8(0x8088B96D, 0x55, 'E');
kmRegionWrite8(0x8088B979, 0x55, 'E');
kmRegionWrite8(0x8088B981, 0x55, 'E');
kmRegionWrite8(0x8088F421, 0x55, 'J');
kmRegionWrite8(0x8087E1E9, 0x55, 'K');

//Free Roam Code
asmFunc Mushrooms() {
    ASM(
  li        r12, 0x1;
  stw       r12, 0x90(r4);
  li        r12, 0x4;
  stw       r12, 0x8C(r4);
  lwz       r0, 0x8C(r4);
  blr;
    )
}

asmFunc Feather() {
    ASM(
  li        r12, 0x1;
  stw       r12, 0x90(r4);
  li        r12, 0xC;
  stw       r12, 0x8C(r4);
  lwz       r0, 0x8C(r4);
  blr;
    )
}

asmFunc AutoDrive1() {
    ASM(
  lwz       r0, 0x18(r30);
  cmpwi     r0, 0;
  bne-      loc_0x10;
  li        r0, 0x1;

loc_0x10:
  blr;
    )
}

asmFunc AutoDrive2() {
    ASM(
  lwz       r3, 0x38(r3);
  cmpwi     r3, 0;
  bne-      loc_0x10;
  li        r3, 0x1;

loc_0x10:
  blr;
    )
}
kmRuntimeUse(0x805349d4);
kmRuntimeUse(0x8053353c);
kmRuntimeUse(0x805a7408);
kmRuntimeUse(0x80633bb0);
kmRuntimeUse(0x8069b40c);
kmRuntimeUse(0x80716638);
kmRuntimeUse(0x80725afc);
kmRuntimeUse(0x80857768);
kmRuntimeUse(0x808577e0);
kmRuntimeUse(0x808409fe);
kmRuntimeUse(0x80840a00);
kmRuntimeUse(0x80571714);
kmRuntimeUse(0x80571dc4);
kmRuntimeUse(0x805867cc);
kmRuntimeUse(0x805954fc);
kmRuntimeUse(0x808b5b1c);
kmRuntimeUse(0x807eee98);
kmRuntimeUse(0x8052F538);
kmRuntimeUse(0x80726270);

extern u8 REGION;
void FreeRoam() {
    kmRuntimeWrite32A(0x805349d4, 0x80A30038);
    kmRuntimeWrite32A(0x8053353c, 0x801F0020);
    kmRuntimeWrite32A(0x805a7408, 0x807D0078);
    kmRuntimeWrite32A(0x80633bb0, 0x3860116E);
    if(REGION == 'P') kmRuntimeWrite32A(0x8069b40c, 0x4BE97C85);
    if(REGION == 'E') kmRuntimeWrite32A(0x8069b40c, 0x4BE975C5);
    if(REGION == 'J') kmRuntimeWrite32A(0x8069b40c, 0x4BE97F99);
    if(REGION == 'K') kmRuntimeWrite32A(0x8069b40c, 0x4BE97935);
    kmRuntimeWrite32A(0x80716638, 0x280400D6);
    kmRuntimeWrite32A(0x80725afc, 0x88030006);
    kmRuntimeWrite32A(0x80857768, 0x40820090);
    kmRuntimeWrite32A(0x808577e0, 0x388000D6);
    kmRuntimeWrite16A(0x808409fe, 0x0070);
    if(REGION != 'E') kmRuntimeWrite32A(0x80840a00, 0x4BFF6D21);
    else kmRuntimeWrite32A(0x80840a00, 0x4BFF9889);
    kmRuntimeWrite16A(0x80571714, 0x4180);
    kmRuntimeWrite16A(0x80571dc4, 0x4182);
    kmRuntimeWrite16A(0x805867cc, 0x4182);
    kmRuntimeWrite32A(0x807eee98, 0x8004008C);
    kmRuntimeWrite32A(0x8052F538, 0x801E0018);
    kmRuntimeWrite32A(0x80726270, 0x80630038);
    if(U16_FREE_ROAM == 0x1) {
        if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_FREEROAM,SETTINGS_FREE_ROAM_LAP_COUNT) == 0) kmRuntimeWrite32A(0x805349d4, 0x38A00002);
        kmRuntimeWrite32A(0x8053353c, 0x380000F0);
        kmRuntimeWrite32A(0x805a7408, 0x386000AA);
        kmRuntimeWrite32A(0x80633bb0, 0x38600048);
        kmRuntimeWrite32A(0x8069b40c, 0x38600000);
        kmRuntimeWrite32A(0x80716638, 0x280401CF);
        kmRuntimeWrite32A(0x80725afc, 0x38000001);
        kmRuntimeWrite32A(0x80857768, 0x60000000);
        kmRuntimeWrite32A(0x808577e0, 0x388001CF);
        kmRuntimeWrite32A(0x808b5b1c, 0x00000000);
        kmRuntimeWrite16A(0x808409fe, 0x001F);
        kmRuntimeWrite32A(0x80840a00, 0x42800015);
        if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_FREEROAM,SETTINGS_FREE_ROAM_FALL_BOUNDARIES) == 0) {
          kmRuntimeWrite16A(0x80571714, 0x4800);
          kmRuntimeWrite16A(0x80571dc4, 0x4800);
          kmRuntimeWrite16A(0x805867cc, 0x4800);
        }
        if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_FREEROAM,SETTINGS_FREE_ROAM_ITEM) == 0) kmRuntimeCallA(0x807eee98, Mushrooms);
        if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_FREEROAM,SETTINGS_FREE_ROAM_ITEM) == 1) kmRuntimeCallA(0x807eee98, Feather);
        if(Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_FREEROAM,SETTINGS_FREE_ROAM_AUTODRIVE) == 1) kmRuntimeCallA(0x8052F538, AutoDrive1), kmRuntimeCallA(0x80726270, AutoDrive2);
    }
}
static PageLoadHook FREEROAM(FreeRoam);

extern u16 GCInput;
extern u16 ClassicInput;
extern u16 WiiInput;
void FreeRoamRespawn() {
    kmRuntimeWrite32A(0x805954fc, 0x80B40004);
    if(U16_FREE_ROAM == 0x1) {
        if(GCInput == 0x0880 || ClassicInput == 0x1000 || WiiInput == 0x1000) kmRuntimeWrite32A(0x805954fc, 0x38A00010);
    }
}
static PageLoadHook2 FREEROAMRESPAWN(FreeRoamRespawn);

void ResetGameModeFlags() {
  const SectionId sectionMode = SectionMgr::sInstance->curSection->sectionId;
  if(sectionMode >= 0x3F && sectionMode <= 0x43) {
    U16_FREE_ROAM = 0;
  }
}
static PageLoadHook2 RESETGAMEMODEFLAGS(ResetGameModeFlags);

kmWrite32(0x80895cc0, 0x00000080);
kmWrite32(0x80895cc4, 0x00FF00F3);
kmWrite32(0x80895cc8, 0x00FF0080);
kmWrite32(0x80895ccc, 0x000000FF);
kmWrite32(0x80895cd0, 0x00FF0000);
kmWrite32(0x80895cd4, 0x00000046);
kmWrite32(0x80895cd8, 0x00FF00FF);
kmWrite32(0x80895cdc, 0x00FF00FF);
kmWrite32(0x80895ce0, 0x00FF00FF);
kmWrite32(0x80895ce4, 0x00FF00FF);
kmWrite32(0x80895ce8, 0x00FF00FF);
kmWrite32(0x80895cec, 0x00FF0046);
kmWrite32(0x80895cf0, 0x0000006F);
kmWrite32(0x80895cf4, 0x00FF00FF);
kmWrite32(0x80895cf8, 0x001300E5);
kmWrite32(0x80895cfc, 0x00FF00FF);
kmWrite32(0x80895d00, 0x001300E5);
kmWrite32(0x80895d04, 0x00FF0046);
kmWrite32(0x80895d08, 0x00FF0000);
kmWrite32(0x80895d0c, 0x000000FF);
kmWrite32(0x80895d10, 0x00FF004F);
kmWrite32(0x80895d14, 0x00FF00FF);
kmWrite32(0x80895d18, 0x00FF004F);
kmWrite32(0x80895d1c, 0x00FF0046);
kmWrite32(0x80895d20, 0x000000BA);
kmWrite32(0x80895d24, 0x000000FF);
kmWrite32(0x80895d28, 0x004C00FF);
kmWrite32(0x80895d2c, 0x008200FF);
kmWrite32(0x80895d30, 0x004C00FF);
kmWrite32(0x80895d34, 0x00820046);
kmWrite32(0x80895d38, 0x00FF00FF);
kmWrite32(0x80895d3c, 0x00FF00D2);
kmWrite32(0x80895d40, 0x00AA00AA);
kmWrite32(0x80895d44, 0x00AA00FF);
kmWrite32(0x80895d48, 0x00000000);
kmWrite32(0x80895d4c, 0x00000046);

kmWrite32(0x8088C04C, 0x48000024);
kmWrite32(0x8088C078, 0x3AE00065);
kmWrite32(0x8088C074, 0x3AA00007);
kmWrite8(0x8088BFF7, 0x01);
}//namespace Race
}//namespace Pulsar