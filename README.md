# Algae - An Insaniquarium 1.1 SDK

This project is aimed to provide a platform for modifying Insaniquarium by PopCap Games with ease.

It is heavily inspired by [Haggle](https://github.com/PeggleCommunity/haggle), a similar effort done to provide a modding platform for Peggle Deluxe built on the same game framework, SexyAppFramework.

Algae is currently *very* early in development! The current state of affairs can be seen down in the [Roadmap](#roadmap) section. If you have a suggestion or comment, please open an [Issue](../../issues) and label it as such, it would be much appreciated!

**Note:** Algae is currently **not** ready for the Steam version of Insaniquarium! I have built the project against a standalone copy, but I will get around to it soon.

## How to Install

First, go to the [Releases](../../releases/latest) page and download the ZIP file from the latest version there. Inside should be a few things that you will need.

Next, you will need to locate your file directory for Insaniquarium. If you have it on Steam, right-click on it in your Library and select "*Manage -> Browse Local Files*", or use the right-click "*Open file location*" if you have it as a standalone Windows copy (as I have).

Lastly, you will simply need to extract the files from the ZIP into the file directory where your game is located. That's it!

## Installing Mods

Mods, configs and logs will all be found in the same place as Insaniquarium's location for user data: "**C:\ProgramData\PopCap Games\Insaniquarium\Algae**". You may need to create the "Algae" folder if it does not exist yet.

To install mods, you will simply need to drop their files into the "mods" folder in there, and they should be loaded when the game starts up.

## Building

The project uses Visual Studio 2022. More info in the future on how to build, but it should be as straightforward as this:
  * Build the solution in the "Release - Win32" configuration (or Debug if you need to, y'know, debug anything).
  * Take the output DLLs (**winmm.dll**, **AlgaeSDK.dll**) and drop them in the same folder as your Insaniquarium installation.
  * Done!

If you are looking to build the project on Linux or Mac, I will get around to looking into a more portable solution eventually!

## Writing your own mods

Information will eventually be provided in the Wiki, including setup and documentation.

## Roadmap

Currently (as of 2026/11/03), Algae is severely under-developed, with just one hook (TitleScreen::Draw) and some basic functions for getting text up on the loading screen. However, despite having limited time to work on it, there is some progress, and I decided that it is far enough along that I'm happy with publishing it. Please follow along as I continue working on it!

- [x] Build out a proper logging system
- [x] Fix folder structure and naming conventions (unhappy with it at the moment)
- [x] Build out std::string interop (turns out we can't just pass a 2022 std::string to 2005, need to figure out a solution)
- [ ] Implement config file ini (kinda like Unity Doorstop's)
- [x] Identify Steam and non-Steam builds and adjust addressing according to each version
  - No difference, learned more while testing and googling, should have more info soon
- [ ] Work on an SDK versioning scheme I actually like
- [ ] Add more event hooks to the SDK
- [ ] Add a resource overriding system (add your own assets without overwriting game files)
- [ ] Add an Algae mod menu on the main menu
- [ ] Algae SDK versioning?
- [ ] WinXP (or some baseline OS) compatibility?
- [ ] Adding new game object types (fish? aliens? items?)

## AI Disclosure

This project is **not** maintained by, created for, MCP-connected with, or otherwise supported by generative AI, and does not accept contributions generated significantly by an LLM. Any works you see in this project are written by a human being first and foremost, and will remain that way. Doing research, writing your own *personal* tools, following examples, or verifying your work with an AI model is totally acceptable.

I am not a fully anti-AI person, but I seek to work on projects with an intential focus on its design, and throwing out a prompt and some tokens does not constitute intentionality to me. I also do not stand for licensing and publishing works made largely by an AI model without the assurance that its training data is ethically sourced (and AFAIK there are no good ones yet, so it's a moot point).

Note that **this can change** in the future, but will be fully disclosed if anything happens (I'm open to suggestions and ideas). Rest assured though, that this project was made by a person who still likes making things themselves, even if it takes longer. <3

## Dependencies

Dependencies will be located in the "deps" folder.

Currently, only [MinHook](https://github.com/TsudaKageyu/minhook) is used, as it's an incredibly useful tool for hooking into processes and building callbacks. I don't think any of this would be possible without it (or it would have taken much longer).
