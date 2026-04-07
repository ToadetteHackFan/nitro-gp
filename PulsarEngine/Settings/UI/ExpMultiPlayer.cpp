#include <kamek.hpp>
#include <MarioKartWii/UI/Page/Menu/MultiPlayer.hpp>
#include <MarioKartWii/Item/ItemManager.hpp>
#include <PulsarSystem.hpp>
#include <UI/UI.hpp>
#include <Settings/UI/SettingsPanel.hpp>
#include <Settings/SettingsParam.hpp>
//Implements 4 TT modes by splitting the "Time Trials" button


namespace Pulsar {
namespace UI {



void CorrectButtonCount(Pages::MultiPlayer* page) {
    const System* system = System::sInstance;
    page->externControlCount = 4;
    new (page) Page;
}
kmCall(0x8062b260, CorrectButtonCount);
kmWrite32(0x8062b27C, 0x60000000);

UIControl* CreateExternalControls(Pages::MultiPlayer* page, u32 id) {
    if(id == page->externControlCount - 1) {
        PushButton* button = new(PushButton);
        page->AddControl(page->controlCount++, *button, 0);
        const char* name =  "Settings1P";
        button->Load(UI::buttonFolder, name, name, page->activePlayerBitfield, 0, false);
        return button;
    }
    return page->Pages::MultiPlayer::CreateExternalControl(id);

}
kmWritePointer(0x808D9D8C, CreateExternalControls);

static void LoadCorrectBRCTR(PushButton& button, const char* folder, const char* ctr, const char* variant, u32 localPlayerField) {
    register int idx;
    asm(mr idx, r28;);
    Pages::MultiPlayer* page = button.parentGroup->GetParentPage<Pages::MultiPlayer>();
    const System* system = System::sInstance;

    u32 varId = idx;
    ctr = "NultiTop";
    char ttVariant[0x15];
    snprintf(ttVariant, 0x15, "Button%d", varId);
    variant = ttVariant;
    button.Load(folder, ctr, variant, localPlayerField, 0, false);
    page->curMovieCount = 0;
}
kmCall(0x8084d320, LoadCorrectBRCTR);

void OnButtonSelect(Pages::MultiPlayer* page, PushButton& button, u32 hudSlotId) {
    const s32 id = button.buttonId;
    u32 bmgId;
    button.buttonId = id;
    if(id == 3) bmgId = BMG_SETTINGSBUTTON_BOTTOM;
    else if(id == 2) bmgId = BMG_TT_MODE_BOTTOM_SINGLE + 5;
    else bmgId = 0xbed + id; 
    page->bottomText->SetMessage(bmgId);
}
kmWritePointer(0x808D9D6C, &OnButtonSelect);

void OnButtonClick(Pages::MultiPlayer* page, PushButton& button, u32 hudSlotId) {
    const u32 id = button.buttonId;
    ItemRainEnabled = false;
    if(id == page->externControlCount - 1) {
        ExpSection::GetSection()->GetPulPage<SettingsPanel>()->prevPageId = PAGE_MULTIPLAYER_MENU;
        page->nextPageId = static_cast<PageId>(SettingsPanel::id);
        page->EndStateAnimated(0, button.GetAnimationFrameSize());
        return;
    }
    if(id == 2) button.buttonId = 0, ItemRainEnabled = true;
    page->Pages::MultiPlayer::OnButtonClick(button, hudSlotId);
    button.buttonId = id;
}
kmWritePointer(0x808BC638, OnButtonClick);

//Disable Corrupt THP from playing
kmWrite8(0x808ADDE0, 0x73);
}//namespace UI
}//namespace Pulsar