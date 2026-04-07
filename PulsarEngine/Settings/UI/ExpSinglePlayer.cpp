#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/SinglePlayer.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>
#include <Settings/UI/SettingsPanel.hpp>
#include <Settings/Settings.hpp>

//Implements 4 TT modes by splitting the "Time Trials" button


namespace Pulsar {
static void SetCC();
namespace UI {



void CorrectButtonCount(Pages::SinglePlayer* page) {
    const System* system = System::sInstance;
    page->externControlCount = 7;
    new (page) Page;
}
kmCall(0x806266b8, CorrectButtonCount);
kmWrite32(0x806266d4, 0x60000000);

UIControl* CreateExternalControls(Pages::SinglePlayer* page, u32 id) {
    if(id == page->externControlCount - 1) {
        PushButton* button = new(PushButton);
        page->AddControl(page->controlCount++, *button, 0);
        const char* name =  "Settings1P";
        button->Load(UI::buttonFolder, name, name, page->activePlayerBitfield, 0, false);
        return button;
    }
    return page->Pages::SinglePlayer::CreateExternalControl(id);

}
kmWritePointer(0x808D9F84, CreateExternalControls);

//kmWrite32(0x8084f080, 0x7F89E378); //get idx in r9
static void LoadCorrectBRCTR(PushButton& button, const char* folder, const char* ctr, const char* variant, u32 localPlayerField) {
    register int idx;
    asm(mr idx, r28;);
    Pages::SinglePlayer* page = button.parentGroup->GetParentPage<Pages::SinglePlayer>();
    const System* system = System::sInstance;

    u32 varId = 0;
    u32 count = page->externControlCount;
    if(count > 5 && (idx == 1 || idx > 3)) {
            ctr = "TingleTop";
            if(idx != 1) varId = idx - 3;
        char ttVariant[0x15];
        snprintf(ttVariant, 0x15, "PulTTFour_%d", varId);
        variant = ttVariant;

    }

    button.Load(folder, ctr, variant, localPlayerField, 0, false);
    page->curMovieCount = 0;
}
kmCall(0x8084f084, LoadCorrectBRCTR);


//kmWrite32(0x8084f08c, 0x60000000);
//kmWrite32(0x8084f094, 0x38030001);
//kmWrite32(0x8084f098, 0x60000000);


void OnButtonSelect(Pages::SinglePlayer* page, PushButton& button, u32 hudSlotId) {
    const s32 id = button.buttonId;
    u32 count = page->externControlCount;
    if(count > 5 && (id == 1 || id > 3)) {
        u32 bmgId;

        if(id == count - 1) bmgId = BMG_SETTINGSBUTTON_BOTTOM;
        else {
            button.buttonId = 1;
            if(id == 5) button.buttonId = 2;
            page->Pages::SinglePlayer::OnExternalButtonSelect(button, hudSlotId);
            button.buttonId = id;
            bmgId = BMG_TT_MODE_BOTTOM_SINGLE + id;
            const System* system = System::sInstance;
        }
        page->bottomText->SetMessage(bmgId);
    }
    else page->Pages::SinglePlayer::OnExternalButtonSelect(button, hudSlotId);
}
kmWritePointer(0x808D9F64, &OnButtonSelect);



//Sets the ttMode based on which button was clicked
void OnButtonClick(Pages::SinglePlayer* page, PushButton& button, u32 hudSlotId) {
    const u32 id = button.buttonId;

    if(page->externControlCount > 4 && id == page->externControlCount - 1) {
        ExpSection::GetSection()->GetPulPage<SettingsPanel>()->prevPageId = PAGE_SINGLE_PLAYER_MENU;
        page->nextPageId = static_cast<PageId>(SettingsPanel::id);
        page->EndStateAnimated(0, button.GetAnimationFrameSize());
        return;
    }

    U16_FREE_ROAM = 0x0;
    ItemRainEnabled = false;
    if(id == 5) button.buttonId = 2, ItemRainEnabled = true;
    if(id == 4) button.buttonId = 1, U16_FREE_ROAM = 0x1;
    page->Pages::SinglePlayer::OnButtonClick(button, hudSlotId);
    button.buttonId = id;
    System* system = System::sInstance;
    if(id == 1 || id == 4) {
        u8 FreeRoamCC = Settings::Mgr::Get().GetSettingValue(Settings::SETTINGSTYPE_FREEROAM,SETTINGS_FREE_ROAM_CC);
        if (FreeRoamCC == 0x0 && U16_FREE_ROAM == 0x1) system->ttMode = TTMODE_150;
        if (FreeRoamCC == 0x1 && U16_FREE_ROAM == 0x1) system->ttMode = TTMODE_200;
        SetCC();
    }
}
kmWritePointer(0x808BBED0, OnButtonClick);
}//namespace UI

//Sets the CC (based on the mode) when retrying after setting a time, as racedata's CC is overwritten usually
static void SetCC() {
    const System* system = System::sInstance;
    EngineClass cc = CC_150;
    if(system->ttMode == TTMODE_200 || system->ttMode == TTMODE_200_FEATHER) cc = CC_100;
    Racedata::sInstance->menusScenario.settings.engineClass = cc;
}
kmBranch(0x805e1ef4, SetCC);
kmBranch(0x805e1d58, SetCC);

//Fix Buttons in Single Player (Toadette Hack Fan)
kmWrite8(0x808AE223, 0x54);

}//namespace Pulsar