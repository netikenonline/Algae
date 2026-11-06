#pragma once
#include <AlgaeTools.h>


namespace Sexy
{
    class GameObject;

    // Event Functions //

    inline constexpr uintptr_t Board_KeyDown                    = 0x540650;
    inline constexpr uintptr_t Board_KeyChar                    = 0x549D70;
    inline constexpr uintptr_t Board_MouseDown                  = 0x543920;
    inline constexpr uintptr_t Board_MouseUp                    = 0x538010;
    inline constexpr uintptr_t Board_ButtonDown                 = 0x54A370;
    inline constexpr uintptr_t Board_ButtonUp                   = 0x538070;
    inline constexpr uintptr_t Board_Update                     = 0x547610;
    inline constexpr uintptr_t Board_Draw                       = 0x53F5F0;
    inline constexpr uintptr_t Board_DrawOverlay                = 0x540470;

    // Functions //

    inline constexpr uintptr_t Board_Init                       = 0x541A20;
    inline constexpr uintptr_t Board_InitStore                  = 0x541200;
    inline constexpr uintptr_t Board_StartLevel                 = 0x5498B0;
    inline constexpr uintptr_t Board_StartBonusRound            = 0x537E20;
    inline constexpr uintptr_t Board_StartVirtualTank           = 0x53C3F0;
    inline constexpr uintptr_t Board_GetGameTime                = 0x537B60;
    inline constexpr uintptr_t Board_PlaySample                 = 0x538230;
    inline constexpr uintptr_t Board_SetBackdrop                = 0x538A10;
    inline constexpr uintptr_t Board_UpdateBackdropColor        = 0x537D30;
    inline constexpr uintptr_t Board_AddBubbles                 = 0x538A50;
    inline constexpr uintptr_t Board_UpdateMoneyLabel           = 0x53A360;
    inline constexpr uintptr_t Board_ShowMessage                = 0x53E950;
    inline constexpr uintptr_t Board_DrawTank                   = 0x538E50;
    inline constexpr uintptr_t Board_DrawWaveImage              = 0x538CF0;
    inline constexpr uintptr_t Board_DrawOverlayLow             = 0x53BD90;
    inline constexpr uintptr_t Board_DrawOverlayHigh            = 0x5400F0;
    inline constexpr uintptr_t Board_DrawBonusRoundHud          = 0x53EAF0;
    inline constexpr uintptr_t Board_UpdateZOrder               = 0x53AA40;
    inline constexpr uintptr_t Board_AddGameObject              = 0x542EE0;
    inline constexpr uintptr_t Board_AddShadow                  = 0x544800;
    inline constexpr uintptr_t Board_AddShadowOfKind            = 0x544370;
    inline constexpr uintptr_t Board_AddGuppy                   = 0x546EF0;
    inline constexpr uintptr_t Board_AddPet                     = 0x544A90;
    inline constexpr uintptr_t Board_RemoveVirtualPet           = 0x53A770;
    inline constexpr uintptr_t Board_AddBreeder                 = 0x5471E0;
    inline constexpr uintptr_t Board_StopTone                   = 0x5384A0;
    inline constexpr uintptr_t Board_GetStoreButton             = 0x538090;
    inline constexpr uintptr_t Board_GetStoreItemName           = 0x538100;
    inline constexpr uintptr_t Board_CreateStoreButton          = 0x5409B0;
    inline constexpr uintptr_t Board_UpdateStoreButton          = 0x5406A0;
    inline constexpr uintptr_t Board_PickSandboxAlien           = 0x537C20;
    inline constexpr uintptr_t Board_BuyStoreItem               = 0x549380;
    inline constexpr uintptr_t Board_PlaySplashSound            = 0x538360;
    inline constexpr uintptr_t Board_BuyEggPiece                = 0x545960;
    inline constexpr uintptr_t Board_GoToBonusRound             = 0x53DC10;
    inline constexpr uintptr_t Board_DrawWavyText               = 0x53DC50;
    inline constexpr uintptr_t Board_DropBreeder                = 0x5470A0;
    inline constexpr uintptr_t Board_PlayBirthSound             = 0x5382C0;
    inline constexpr uintptr_t Board_FindVirtualFish            = 0x53A810;
    inline constexpr uintptr_t Board_ShowVirtualFish            = 0x5449C0;
    inline constexpr uintptr_t Board_AddCarnivore               = 0x544C00;
    inline constexpr uintptr_t Board_AddStarcatcher             = 0x545260;
    inline constexpr uintptr_t Board_AddGuppycruncher           = 0x545430;
    inline constexpr uintptr_t Board_AddLarva                   = 0x5445A0;
    inline constexpr uintptr_t Board_AddBeetlemuncher           = 0x545080;
    inline constexpr uintptr_t Board_CountFoodNeeds             = 0x53A3C0;
    inline constexpr uintptr_t Board_CountFoods                 = 0x5397A0;
    inline constexpr uintptr_t Board_AddVirtualFood             = 0x547530;
    inline constexpr uintptr_t Board_AddVirtualGuppy            = 0x547490;
    inline constexpr uintptr_t Board_AddVirtualStar             = 0x544630;
    inline constexpr uintptr_t Board_AddVirtualLarva            = 0x544720;
    inline constexpr uintptr_t Board_AddVirtualCarnivore        = 0x5474C0;
    inline constexpr uintptr_t Board_AddVirtualUltravore        = 0x5474F0;
    inline constexpr uintptr_t Board_AddVirtualFoodOfKind       = 0x543570;
    inline constexpr uintptr_t Board_AddUltravore               = 0x544E60;
    inline constexpr uintptr_t Board_RemoveGameWidgets          = 0x53C480;
    inline constexpr uintptr_t Board_CreateVirtualButtons       = 0x53E280;
    inline constexpr uintptr_t Board_ActivateCheat              = 0x5404A0;
    inline constexpr uintptr_t Board_UpdateVirtualButtons       = 0x53A4F0;
    inline constexpr uintptr_t Board_UpdateObjectDays           = 0x53A450;
    inline constexpr uintptr_t Board_UpdatePetBackdrops         = 0x539A50;
    inline constexpr uintptr_t Board_UpdateHasVirtualFish       = 0x53A980;
    inline constexpr uintptr_t Board_GetFreeVirtualId           = 0x53A890;
    inline constexpr uintptr_t Board_AddVirtualFish             = 0x544940;
    inline constexpr uintptr_t Board_FeedVirtualTank            = 0x5492B0;
    inline constexpr uintptr_t Board_LoadGame                   = 0x546AA0;
    inline constexpr uintptr_t Board_Sync                       = 0x546240;
    inline constexpr uintptr_t Board_WriteSaveGame              = 0x546990;
    inline constexpr uintptr_t Board_RestoreMusic               = 0x538940;
    inline constexpr uintptr_t Board_RemoveWildObjects          = 0x5437B0;
    inline constexpr uintptr_t Board_WelcomeToEmptyTank         = 0x53AA00;
    inline constexpr uintptr_t Board_IsTankLevel                = 0x537BB0;
    inline constexpr uintptr_t Board_IsFirstLevel               = 0x537B80;
    inline constexpr uintptr_t Board_HasLivingFish              = 0x5392A0;
    inline constexpr uintptr_t Board_HasUltravore               = 0x4E3ED0;
    inline constexpr uintptr_t Board_HasGuppycruncher           = 0x4E3F00;
    inline constexpr uintptr_t Board_HasBeetlemuncher           = 0x4E3F30;
    inline constexpr uintptr_t Board_HasBreeder                 = 0x4E3F60;
    inline constexpr uintptr_t Board_SetStorePriceColor         = 0x538700;
    inline constexpr uintptr_t Board_SetStorePrice              = 0x5380C0;
    inline constexpr uintptr_t Board_GetBubblerPos              = 0x538B60;
    inline constexpr uintptr_t Board_AddBubbleAt                = 0x538AC0;
    inline constexpr uintptr_t Board_PlayLaserSound             = 0x538AE0;
    inline constexpr uintptr_t Board_StartBonusTimer            = 0x537F40;
    inline constexpr uintptr_t Board_CollectMoney               = 0x53C2D0;
    inline constexpr uintptr_t Board_PickVirtualTankAlien       = 0x5394E0;
    inline constexpr uintptr_t Board_PickVirtualTankAlienSpawn  = 0x539330;
    inline constexpr uintptr_t Board_GetWarpPos                 = 0x538C10;
    inline constexpr uintptr_t Board_GetCollectedValue          = 0x53A0B0;
    inline constexpr uintptr_t Board_SetFishClickable           = 0x539AD0;
    inline constexpr uintptr_t Board_SpawnBonusCoins            = 0x5460F0;
    inline constexpr uintptr_t Board_Sneeze                     = 0x543F40;
    inline constexpr uintptr_t Board_CanDropFood                = 0x540B30;
    inline constexpr uintptr_t Board_DropFood                   = 0x543280;
    inline constexpr uintptr_t Board_DropTreat                  = 0x5434E0;
    inline constexpr uintptr_t Board_ClickFood                  = 0x539F30;
    inline constexpr uintptr_t Board_RightClick                 = 0x53BFB0;
    inline constexpr uintptr_t Board_RightClickPet              = 0x539630;
    inline constexpr uintptr_t Board_FindPresto                 = 0x539540;
    inline constexpr uintptr_t Board_IsAlienPresent             = 0x4DA780;
    inline constexpr uintptr_t Board_CanPlaySample              = 0x5381F0;
    inline constexpr uintptr_t Board_UpdateTonePlayer           = 0x538060;
    inline constexpr uintptr_t Board_IsTonePlaying              = 0x538490;
    inline constexpr uintptr_t Board_StartTone                  = 0x540CC0;
    inline constexpr uintptr_t Board_PlayPointsSound            = 0x5383D0;
    inline constexpr uintptr_t Board_PlayChompSound             = 0x5384C0;
    inline constexpr uintptr_t Board_PlayDeathSound             = 0x538610;
    inline constexpr uintptr_t Board_AddMoney                   = 0x53C1E0;
    inline constexpr uintptr_t Board_RefundFood                 = 0x53C280;
    inline constexpr uintptr_t Board_ShowFloatingText           = 0x5444E0;
    inline constexpr uintptr_t Board_AddEffect                  = 0x5436F0;
    inline constexpr uintptr_t Board_DropCoin                   = 0x544430;
    inline constexpr uintptr_t Board_PlayDiamondSound           = 0x538470;
    inline constexpr uintptr_t Board_PlayBiteSound              = 0x538560;
    inline constexpr uintptr_t Board_GetBonusPotPos             = 0x538CD0;
    inline constexpr uintptr_t Board_HasMissile                 = 0x4E3EA0;
    inline constexpr uintptr_t Board_ClickThroughToAlien        = 0x539D40;
    inline constexpr uintptr_t Board_BonusChain                 = 0x545E20;
    inline constexpr uintptr_t Board_AddDeadFish                = 0x5441F0;
    inline constexpr uintptr_t Board_DropGuppy                  = 0x546D70;
    inline constexpr uintptr_t Board_DropStarGuppy              = 0x547310;
    inline constexpr uintptr_t Board_ReviveGuppy                = 0x546FC0;
    inline constexpr uintptr_t Board_ReviveCarnivore            = 0x544D80;
    inline constexpr uintptr_t Board_ReviveUltravore            = 0x544FE0;
    inline constexpr uintptr_t Board_ReviveBeetlemuncher        = 0x5451C0;
    inline constexpr uintptr_t Board_ReviveStarcatcher          = 0x545360;
    inline constexpr uintptr_t Board_ReviveGuppycruncher        = 0x5454F0;
    inline constexpr uintptr_t Board_ReviveBreeder              = 0x547270;
    inline constexpr uintptr_t Board_RemoveGameObject           = 0x541D90;
    inline constexpr uintptr_t Board_AddLaserShot               = 0x543640;
    inline constexpr uintptr_t Board_SpawnAlien                 = 0x545620;
    inline constexpr uintptr_t Board_SpawnAlienAnywhere         = 0x5475B0;
    inline constexpr uintptr_t Board_AddMiniSylvester           = 0x545580;
    inline constexpr uintptr_t Board_AddMissile                 = 0x544130;
    inline constexpr uintptr_t Board_AddDeadAlien               = 0x5442C0;
    inline constexpr uintptr_t Board_ClearMessage               = 0x537F90;
    inline constexpr uintptr_t Board_PlayBounceSound            = 0x538340;
    inline constexpr uintptr_t Board_CheckAliensGone            = 0x539C90;
    inline constexpr uintptr_t Board_SaveGame                   = 0x5497A0;
    inline constexpr uintptr_t Board_GetGameTimeSeconds         = 0x538040;
    inline constexpr uintptr_t Board_Pause                      = 0x53DB80;
    inline constexpr uintptr_t Board_CanSaveGame                = 0x537BF0;
    inline constexpr uintptr_t Board_OptionsApplied             = 0x539FE0;

    class Board
    {
    public:
        inline GameObject* DropGuppy() { return Algae::Call<GameObject*>(Board_DropGuppy, this); }
    };
}
