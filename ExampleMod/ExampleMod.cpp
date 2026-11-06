#include <string>
#include <AlgaeSDK.h>

static void __cdecl DrawModLoaded(Sexy::Widget* self, Sexy::Graphics* g)
{
    Sexy::Font* font = Algae::ReadGlobal<Sexy::Font*>(Sexy::FONT_JUNGLEFEVER17OUTLINE);

    std::string text = "Hello World!";
    Sexy::Font* oldFont = g->GetFont();
    Sexy::Color oldColor = g->GetColor();

    g->SetFont(font);
    g->SetColor(Sexy::Color{ 255, 236, 145, 255 });
    int width = font->StringWidth(text);
    g->DrawString(text, 640 - width - 12, 24);

    g->SetFont(oldFont);
    g->SetColor(oldColor);
}

extern "C" __declspec(dllexport) void ModInit(const ModHost* host)
{
    Algae_AddPostHook(Sexy::Addr::TitleScreen_Draw, DrawModLoaded);
    Algae_Log("ExampleMod initialized!");
}
