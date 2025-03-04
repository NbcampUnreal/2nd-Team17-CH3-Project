
#include "UI/UI_WinScreen.h"

void UUI_WinScreen::NativeConstruct()
{
    Super::NativeConstruct();

    PlayWinVideo();
}

void UUI_WinScreen::PlayWinVideo()
{
    if (WinMediaPlayer && WinMediaSource)
    {
        WinMediaPlayer->OpenSource(WinMediaSource);  // 비디오 재생
    }
}