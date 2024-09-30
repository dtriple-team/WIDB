/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <new>
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <platform/driver/lcd/LCD16bpp.hpp>
#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataView.hpp>
#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataPresenter.hpp>
#include <gui/sleepscreen_screen/SleepScreenView.hpp>
#include <gui/sleepscreen_screen/SleepScreenPresenter.hpp>
#include <gui/spo2screen_screen/Spo2ScreenView.hpp>
#include <gui/spo2screen_screen/Spo2ScreenPresenter.hpp>
#include <gui/heartratescreen_screen/HeartrateScreenView.hpp>
#include <gui/heartratescreen_screen/HeartrateScreenPresenter.hpp>
#include <gui/stepsscreen_screen/StepsScreenView.hpp>
#include <gui/stepsscreen_screen/StepsScreenPresenter.hpp>
#include <gui/heartratedetail_screen/HeartrateDetailView.hpp>
#include <gui/heartratedetail_screen/HeartrateDetailPresenter.hpp>
#include <gui/spo2detail_screen/Spo2DetailView.hpp>
#include <gui/spo2detail_screen/Spo2DetailPresenter.hpp>
#include <gui/swipedownfromhome_screen/swipedownfromHomeView.hpp>
#include <gui/swipedownfromhome_screen/swipedownfromHomePresenter.hpp>
#include <gui/settingscreen_screen/SettingScreenView.hpp>
#include <gui/settingscreen_screen/SettingScreenPresenter.hpp>
#include <gui/screensetting_screen/screenSettingView.hpp>
#include <gui/screensetting_screen/screenSettingPresenter.hpp>
#include <gui/screenontimesetting_screen/screenontimeSettingView.hpp>
#include <gui/screenontimesetting_screen/screenontimeSettingPresenter.hpp>
#include <gui/screenbrightnesssetting_screen/screenbrightnessSettingView.hpp>
#include <gui/screenbrightnesssetting_screen/screenbrightnessSettingPresenter.hpp>
#include <gui/soundnhapticssetting_screen/soundnhapticsSettingView.hpp>
#include <gui/soundnhapticssetting_screen/soundnhapticsSettingPresenter.hpp>
#include <gui/languagesetting_screen/languageSettingView.hpp>
#include <gui/languagesetting_screen/languageSettingPresenter.hpp>
#include <gui/informationsetting_screen/informationSettingView.hpp>
#include <gui/informationsetting_screen/informationSettingPresenter.hpp>
#include <gui/deviceinfosetting_screen/deviceInfoSettingView.hpp>
#include <gui/deviceinfosetting_screen/deviceInfoSettingPresenter.hpp>
#include <gui/networkinfosetting_screen/networkInfoSettingView.hpp>
#include <gui/networkinfosetting_screen/networkInfoSettingPresenter.hpp>
#include <gui/systemsetting_screen/systemSettingView.hpp>
#include <gui/systemsetting_screen/systemSettingPresenter.hpp>
#include <gui/turnoffscreen_screen/turnoffScreenView.hpp>
#include <gui/turnoffscreen_screen/turnoffScreenPresenter.hpp>
#include <gui/falldetected_screen/fallDetectedView.hpp>
#include <gui/falldetected_screen/fallDetectedPresenter.hpp>
#include <gui/initblackscreen_screen/initBlackScreenView.hpp>
#include <gui/initblackscreen_screen/initBlackScreenPresenter.hpp>
#include <gui/temphome_screen/tempHomeView.hpp>
#include <gui/temphome_screen/tempHomePresenter.hpp>

using namespace touchgfx;

FrontendApplicationBase::FrontendApplicationBase(Model& m, FrontendHeap& heap)
    : touchgfx::MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
    touchgfx::HAL::getInstance()->setDisplayOrientation(touchgfx::ORIENTATION_PORTRAIT);
    touchgfx::Texts::setLanguage(GB);
    reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableTextureMapperAll();
    reinterpret_cast<touchgfx::LCD16bpp&>(touchgfx::HAL::lcd()).enableDecompressorL8_All();
}

/*
 * Screen Transition Declarations
 */

// HomeScreenWithBiodata

void FrontendApplicationBase::gotoHomeScreenWithBiodataScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoHomeScreenWithBiodataScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoHomeScreenWithBiodataScreenNoTransitionImpl()
{
    touchgfx::makeTransition<HomeScreenWithBiodataView, HomeScreenWithBiodataPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoHomeScreenWithBiodataScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoHomeScreenWithBiodataScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoHomeScreenWithBiodataScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<HomeScreenWithBiodataView, HomeScreenWithBiodataPresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoHomeScreenWithBiodataScreenWipeTransitionSouth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoHomeScreenWithBiodataScreenWipeTransitionSouthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoHomeScreenWithBiodataScreenWipeTransitionSouthImpl()
{
    touchgfx::makeTransition<HomeScreenWithBiodataView, HomeScreenWithBiodataPresenter, touchgfx::WipeTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// HeartrateDetail

void FrontendApplicationBase::gotoHeartrateDetailScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoHeartrateDetailScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoHeartrateDetailScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<HeartrateDetailView, HeartrateDetailPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoHeartrateDetailScreenWipeTransitionSouth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoHeartrateDetailScreenWipeTransitionSouthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoHeartrateDetailScreenWipeTransitionSouthImpl()
{
    touchgfx::makeTransition<HeartrateDetailView, HeartrateDetailPresenter, touchgfx::WipeTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// Spo2Detail

void FrontendApplicationBase::gotoSpo2DetailScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoSpo2DetailScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoSpo2DetailScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<Spo2DetailView, Spo2DetailPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoSpo2DetailScreenWipeTransitionSouth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoSpo2DetailScreenWipeTransitionSouthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoSpo2DetailScreenWipeTransitionSouthImpl()
{
    touchgfx::makeTransition<Spo2DetailView, Spo2DetailPresenter, touchgfx::WipeTransition<SOUTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// swipedownfromHome

void FrontendApplicationBase::gotoswipedownfromHomeScreenCoverTransitionNorth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoswipedownfromHomeScreenCoverTransitionNorthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoswipedownfromHomeScreenCoverTransitionNorthImpl()
{
    touchgfx::makeTransition<swipedownfromHomeView, swipedownfromHomePresenter, touchgfx::CoverTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoswipedownfromHomeScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoswipedownfromHomeScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoswipedownfromHomeScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<swipedownfromHomeView, swipedownfromHomePresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// SettingScreen

void FrontendApplicationBase::gotoSettingScreenScreenWipeTransitionNorth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoSettingScreenScreenWipeTransitionNorthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoSettingScreenScreenWipeTransitionNorthImpl()
{
    touchgfx::makeTransition<SettingScreenView, SettingScreenPresenter, touchgfx::WipeTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoSettingScreenScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoSettingScreenScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoSettingScreenScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<SettingScreenView, SettingScreenPresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// screenSetting

void FrontendApplicationBase::gotoscreenSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoscreenSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoscreenSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<screenSettingView, screenSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoscreenSettingScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoscreenSettingScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoscreenSettingScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<screenSettingView, screenSettingPresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// screenontimeSetting

void FrontendApplicationBase::gotoscreenontimeSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoscreenontimeSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoscreenontimeSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<screenontimeSettingView, screenontimeSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// screenbrightnessSetting

void FrontendApplicationBase::gotoscreenbrightnessSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoscreenbrightnessSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoscreenbrightnessSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<screenbrightnessSettingView, screenbrightnessSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// soundnhapticsSetting

void FrontendApplicationBase::gotosoundnhapticsSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotosoundnhapticsSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotosoundnhapticsSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<soundnhapticsSettingView, soundnhapticsSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// languageSetting

void FrontendApplicationBase::gotolanguageSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotolanguageSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotolanguageSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<languageSettingView, languageSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// informationSetting

void FrontendApplicationBase::gotoinformationSettingScreenWipeTransitionNorth()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoinformationSettingScreenWipeTransitionNorthImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoinformationSettingScreenWipeTransitionNorthImpl()
{
    touchgfx::makeTransition<informationSettingView, informationSettingPresenter, touchgfx::WipeTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoinformationSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoinformationSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoinformationSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<informationSettingView, informationSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplicationBase::gotoinformationSettingScreenWipeTransitionWest()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoinformationSettingScreenWipeTransitionWestImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoinformationSettingScreenWipeTransitionWestImpl()
{
    touchgfx::makeTransition<informationSettingView, informationSettingPresenter, touchgfx::WipeTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// deviceInfoSetting

void FrontendApplicationBase::gotodeviceInfoSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotodeviceInfoSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotodeviceInfoSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<deviceInfoSettingView, deviceInfoSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// networkInfoSetting

void FrontendApplicationBase::gotonetworkInfoSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotonetworkInfoSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotonetworkInfoSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<networkInfoSettingView, networkInfoSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// systemSetting

void FrontendApplicationBase::gotosystemSettingScreenCoverTransitionEast()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotosystemSettingScreenCoverTransitionEastImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotosystemSettingScreenCoverTransitionEastImpl()
{
    touchgfx::makeTransition<systemSettingView, systemSettingPresenter, touchgfx::CoverTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// turnoffScreen

void FrontendApplicationBase::gototurnoffScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gototurnoffScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gototurnoffScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<turnoffScreenView, turnoffScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// fallDetected

void FrontendApplicationBase::gotofallDetectedScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotofallDetectedScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotofallDetectedScreenNoTransitionImpl()
{
    touchgfx::makeTransition<fallDetectedView, fallDetectedPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

// initBlackScreen

void FrontendApplicationBase::gotoinitBlackScreenScreenNoTransition()
{
    transitionCallback = touchgfx::Callback<FrontendApplicationBase>(this, &FrontendApplicationBase::gotoinitBlackScreenScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplicationBase::gotoinitBlackScreenScreenNoTransitionImpl()
{
    touchgfx::makeTransition<initBlackScreenView, initBlackScreenPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}
