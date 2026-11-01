#include <windows.h>

#define WINMM_EXPORT_COUNT 193

extern "C" FARPROC winmmList [WINMM_EXPORT_COUNT] = {};

#define PROXY(i, name) extern "C" __declspec(naked) void _##name() { __asm { jmp dword ptr [winmmList + i * 4] } }

static const char* const winmmNames[WINMM_EXPORT_COUNT] =
{
    MAKEINTRESOURCEA(2),
    "mciExecute",
    "CloseDriver",
    "DefDriverProc",
    "DriverCallback",
    "DrvGetModuleHandle",
    "GetDriverModuleHandle",
    "NotifyCallbackData",
    "OpenDriver",
    "PlaySound",
    "PlaySoundA",
    "PlaySoundW",
    "SendDriverMessage",
    "WOW32DriverCallback",
    "WOW32ResolveMultiMediaHandle",
    "WOWAppExit",
    "aux32Message",
    "auxGetDevCapsA",
    "auxGetDevCapsW",
    "auxGetNumDevs",
    "auxGetVolume",
    "auxOutMessage",
    "auxSetVolume",
    "joy32Message",
    "joyConfigChanged",
    "joyGetDevCapsA",
    "joyGetDevCapsW",
    "joyGetNumDevs",
    "joyGetPos",
    "joyGetPosEx",
    "joyGetThreshold",
    "joyReleaseCapture",
    "joySetCapture",
    "joySetThreshold",
    "mci32Message",
    "mciDriverNotify",
    "mciDriverYield",
    "mciFreeCommandResource",
    "mciGetCreatorTask",
    "mciGetDeviceIDA",
    "mciGetDeviceIDFromElementIDA",
    "mciGetDeviceIDFromElementIDW",
    "mciGetDeviceIDW",
    "mciGetDriverData",
    "mciGetErrorStringA",
    "mciGetErrorStringW",
    "mciGetYieldProc",
    "mciLoadCommandResource",
    "mciSendCommandA",
    "mciSendCommandW",
    "mciSendStringA",
    "mciSendStringW",
    "mciSetDriverData",
    "mciSetYieldProc",
    "mid32Message",
    "midiConnect",
    "midiDisconnect",
    "midiInAddBuffer",
    "midiInClose",
    "midiInGetDevCapsA",
    "midiInGetDevCapsW",
    "midiInGetErrorTextA",
    "midiInGetErrorTextW",
    "midiInGetID",
    "midiInGetNumDevs",
    "midiInMessage",
    "midiInOpen",
    "midiInPrepareHeader",
    "midiInReset",
    "midiInStart",
    "midiInStop",
    "midiInUnprepareHeader",
    "midiOutCacheDrumPatches",
    "midiOutCachePatches",
    "midiOutClose",
    "midiOutGetDevCapsA",
    "midiOutGetDevCapsW",
    "midiOutGetErrorTextA",
    "midiOutGetErrorTextW",
    "midiOutGetID",
    "midiOutGetNumDevs",
    "midiOutGetVolume",
    "midiOutLongMsg",
    "midiOutMessage",
    "midiOutOpen",
    "midiOutPrepareHeader",
    "midiOutReset",
    "midiOutSetVolume",
    "midiOutShortMsg",
    "midiOutUnprepareHeader",
    "midiStreamClose",
    "midiStreamOpen",
    "midiStreamOut",
    "midiStreamPause",
    "midiStreamPosition",
    "midiStreamProperty",
    "midiStreamRestart",
    "midiStreamStop",
    "mixerClose",
    "mixerGetControlDetailsA",
    "mixerGetControlDetailsW",
    "mixerGetDevCapsA",
    "mixerGetDevCapsW",
    "mixerGetID",
    "mixerGetLineControlsA",
    "mixerGetLineControlsW",
    "mixerGetLineInfoA",
    "mixerGetLineInfoW",
    "mixerGetNumDevs",
    "mixerMessage",
    "mixerOpen",
    "mixerSetControlDetails",
    "mmDrvInstall",
    "mmGetCurrentTask",
    "mmTaskBlock",
    "mmTaskCreate",
    "mmTaskSignal",
    "mmTaskYield",
    "mmioAdvance",
    "mmioAscend",
    "mmioClose",
    "mmioCreateChunk",
    "mmioDescend",
    "mmioFlush",
    "mmioGetInfo",
    "mmioInstallIOProcA",
    "mmioInstallIOProcW",
    "mmioOpenA",
    "mmioOpenW",
    "mmioRead",
    "mmioRenameA",
    "mmioRenameW",
    "mmioSeek",
    "mmioSendMessage",
    "mmioSetBuffer",
    "mmioSetInfo",
    "mmioStringToFOURCCA",
    "mmioStringToFOURCCW",
    "mmioWrite",
    "mmsystemGetVersion",
    "mod32Message",
    "mxd32Message",
    "sndPlaySoundA",
    "sndPlaySoundW",
    "tid32Message",
    "timeBeginPeriod",
    "timeEndPeriod",
    "timeGetDevCaps",
    "timeGetSystemTime",
    "timeGetTime",
    "timeKillEvent",
    "timeSetEvent",
    "waveInAddBuffer",
    "waveInClose",
    "waveInGetDevCapsA",
    "waveInGetDevCapsW",
    "waveInGetErrorTextA",
    "waveInGetErrorTextW",
    "waveInGetID",
    "waveInGetNumDevs",
    "waveInGetPosition",
    "waveInMessage",
    "waveInOpen",
    "waveInPrepareHeader",
    "waveInReset",
    "waveInStart",
    "waveInStop",
    "waveInUnprepareHeader",
    "waveOutBreakLoop",
    "waveOutClose",
    "waveOutGetDevCapsA",
    "waveOutGetDevCapsW",
    "waveOutGetErrorTextA",
    "waveOutGetErrorTextW",
    "waveOutGetID",
    "waveOutGetNumDevs",
    "waveOutGetPitch",
    "waveOutGetPlaybackRate",
    "waveOutGetPosition",
    "waveOutGetVolume",
    "waveOutMessage",
    "waveOutOpen",
    "waveOutPause",
    "waveOutPrepareHeader",
    "waveOutReset",
    "waveOutRestart",
    "waveOutSetPitch",
    "waveOutSetPlaybackRate",
    "waveOutSetVolume",
    "waveOutUnprepareHeader",
    "waveOutWrite",
    "wid32Message",
    "wod32Message",
};

// Build out function declarations to match module definitions (winmm.def)

PROXY(0, noname)
PROXY(1, mciExecute)
PROXY(2, CloseDriver)
PROXY(3, DefDriverProc)
PROXY(4, DriverCallback)
PROXY(5, DrvGetModuleHandle)
PROXY(6, GetDriverModuleHandle)
PROXY(7, NotifyCallbackData)
PROXY(8, OpenDriver)
PROXY(9, PlaySound)
PROXY(10, PlaySoundA)
PROXY(11, PlaySoundW)
PROXY(12, SendDriverMessage)
PROXY(13, WOW32DriverCallback)
PROXY(14, WOW32ResolveMultiMediaHandle)
PROXY(15, WOWAppExit)
PROXY(16, aux32Message)
PROXY(17, auxGetDevCapsA)
PROXY(18, auxGetDevCapsW)
PROXY(19, auxGetNumDevs)
PROXY(20, auxGetVolume)
PROXY(21, auxOutMessage)
PROXY(22, auxSetVolume)
PROXY(23, joy32Message)
PROXY(24, joyConfigChanged)
PROXY(25, joyGetDevCapsA)
PROXY(26, joyGetDevCapsW)
PROXY(27, joyGetNumDevs)
PROXY(28, joyGetPos)
PROXY(29, joyGetPosEx)
PROXY(30, joyGetThreshold)
PROXY(31, joyReleaseCapture)
PROXY(32, joySetCapture)
PROXY(33, joySetThreshold)
PROXY(34, mci32Message)
PROXY(35, mciDriverNotify)
PROXY(36, mciDriverYield)
PROXY(37, mciFreeCommandResource)
PROXY(38, mciGetCreatorTask)
PROXY(39, mciGetDeviceIDA)
PROXY(40, mciGetDeviceIDFromElementIDA)
PROXY(41, mciGetDeviceIDFromElementIDW)
PROXY(42, mciGetDeviceIDW)
PROXY(43, mciGetDriverData)
PROXY(44, mciGetErrorStringA)
PROXY(45, mciGetErrorStringW)
PROXY(46, mciGetYieldProc)
PROXY(47, mciLoadCommandResource)
PROXY(48, mciSendCommandA)
PROXY(49, mciSendCommandW)
PROXY(50, mciSendStringA)
PROXY(51, mciSendStringW)
PROXY(52, mciSetDriverData)
PROXY(53, mciSetYieldProc)
PROXY(54, mid32Message)
PROXY(55, midiConnect)
PROXY(56, midiDisconnect)
PROXY(57, midiInAddBuffer)
PROXY(58, midiInClose)
PROXY(59, midiInGetDevCapsA)
PROXY(60, midiInGetDevCapsW)
PROXY(61, midiInGetErrorTextA)
PROXY(62, midiInGetErrorTextW)
PROXY(63, midiInGetID)
PROXY(64, midiInGetNumDevs)
PROXY(65, midiInMessage)
PROXY(66, midiInOpen)
PROXY(67, midiInPrepareHeader)
PROXY(68, midiInReset)
PROXY(69, midiInStart)
PROXY(70, midiInStop)
PROXY(71, midiInUnprepareHeader)
PROXY(72, midiOutCacheDrumPatches)
PROXY(73, midiOutCachePatches)
PROXY(74, midiOutClose)
PROXY(75, midiOutGetDevCapsA)
PROXY(76, midiOutGetDevCapsW)
PROXY(77, midiOutGetErrorTextA)
PROXY(78, midiOutGetErrorTextW)
PROXY(79, midiOutGetID)
PROXY(80, midiOutGetNumDevs)
PROXY(81, midiOutGetVolume)
PROXY(82, midiOutLongMsg)
PROXY(83, midiOutMessage)
PROXY(84, midiOutOpen)
PROXY(85, midiOutPrepareHeader)
PROXY(86, midiOutReset)
PROXY(87, midiOutSetVolume)
PROXY(88, midiOutShortMsg)
PROXY(89, midiOutUnprepareHeader)
PROXY(90, midiStreamClose)
PROXY(91, midiStreamOpen)
PROXY(92, midiStreamOut)
PROXY(93, midiStreamPause)
PROXY(94, midiStreamPosition)
PROXY(95, midiStreamProperty)
PROXY(96, midiStreamRestart)
PROXY(97, midiStreamStop)
PROXY(98, mixerClose)
PROXY(99, mixerGetControlDetailsA)
PROXY(100, mixerGetControlDetailsW)
PROXY(101, mixerGetDevCapsA)
PROXY(102, mixerGetDevCapsW)
PROXY(103, mixerGetID)
PROXY(104, mixerGetLineControlsA)
PROXY(105, mixerGetLineControlsW)
PROXY(106, mixerGetLineInfoA)
PROXY(107, mixerGetLineInfoW)
PROXY(108, mixerGetNumDevs)
PROXY(109, mixerMessage)
PROXY(110, mixerOpen)
PROXY(111, mixerSetControlDetails)
PROXY(112, mmDrvInstall)
PROXY(113, mmGetCurrentTask)
PROXY(114, mmTaskBlock)
PROXY(115, mmTaskCreate)
PROXY(116, mmTaskSignal)
PROXY(117, mmTaskYield)
PROXY(118, mmioAdvance)
PROXY(119, mmioAscend)
PROXY(120, mmioClose)
PROXY(121, mmioCreateChunk)
PROXY(122, mmioDescend)
PROXY(123, mmioFlush)
PROXY(124, mmioGetInfo)
PROXY(125, mmioInstallIOProcA)
PROXY(126, mmioInstallIOProcW)
PROXY(127, mmioOpenA)
PROXY(128, mmioOpenW)
PROXY(129, mmioRead)
PROXY(130, mmioRenameA)
PROXY(131, mmioRenameW)
PROXY(132, mmioSeek)
PROXY(133, mmioSendMessage)
PROXY(134, mmioSetBuffer)
PROXY(135, mmioSetInfo)
PROXY(136, mmioStringToFOURCCA)
PROXY(137, mmioStringToFOURCCW)
PROXY(138, mmioWrite)
PROXY(139, mmsystemGetVersion)
PROXY(140, mod32Message)
PROXY(141, mxd32Message)
PROXY(142, sndPlaySoundA)
PROXY(143, sndPlaySoundW)
PROXY(144, tid32Message)
PROXY(145, timeBeginPeriod)
PROXY(146, timeEndPeriod)
PROXY(147, timeGetDevCaps)
PROXY(148, timeGetSystemTime)
PROXY(149, timeGetTime)
PROXY(150, timeKillEvent)
PROXY(151, timeSetEvent)
PROXY(152, waveInAddBuffer)
PROXY(153, waveInClose)
PROXY(154, waveInGetDevCapsA)
PROXY(155, waveInGetDevCapsW)
PROXY(156, waveInGetErrorTextA)
PROXY(157, waveInGetErrorTextW)
PROXY(158, waveInGetID)
PROXY(159, waveInGetNumDevs)
PROXY(160, waveInGetPosition)
PROXY(161, waveInMessage)
PROXY(162, waveInOpen)
PROXY(163, waveInPrepareHeader)
PROXY(164, waveInReset)
PROXY(165, waveInStart)
PROXY(166, waveInStop)
PROXY(167, waveInUnprepareHeader)
PROXY(168, waveOutBreakLoop)
PROXY(169, waveOutClose)
PROXY(170, waveOutGetDevCapsA)
PROXY(171, waveOutGetDevCapsW)
PROXY(172, waveOutGetErrorTextA)
PROXY(173, waveOutGetErrorTextW)
PROXY(174, waveOutGetID)
PROXY(175, waveOutGetNumDevs)
PROXY(176, waveOutGetPitch)
PROXY(177, waveOutGetPlaybackRate)
PROXY(178, waveOutGetPosition)
PROXY(179, waveOutGetVolume)
PROXY(180, waveOutMessage)
PROXY(181, waveOutOpen)
PROXY(182, waveOutPause)
PROXY(183, waveOutPrepareHeader)
PROXY(184, waveOutReset)
PROXY(185, waveOutRestart)
PROXY(186, waveOutSetPitch)
PROXY(187, waveOutSetPlaybackRate)
PROXY(188, waveOutSetVolume)
PROXY(189, waveOutUnprepareHeader)
PROXY(190, waveOutWrite)
PROXY(191, wid32Message)
PROXY(192, wod32Message)

void LoadWinMM()
{
    wchar_t aPath[MAX_PATH];
    UINT aLen = GetSystemDirectoryW(aPath, MAX_PATH - 12);
    lstrcatW(aPath, L"\\winmm.dll");
    HMODULE aReal = LoadLibraryW(aPath);
    if (aReal != NULL)
    {
        for (int i = 0; i < WINMM_EXPORT_COUNT; i++)
        {
            winmmList[i] = GetProcAddress(aReal, winmmNames[i]);
        }
    }
}
