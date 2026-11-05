# Algae - An Insaniquarium 1.1 SDK

This project is aimed to provide a platform for modifying Insaniquarium by PopCap Games with ease.

It is heavily inspired by [Haggle](https://github.com/PeggleCommunity/haggle), a similar effort done to provide a modding platform for Peggle Deluxe built on the same game framework, SexyAppFramework.

Algae is currently *very* early in development! The current state of affairs can be seen down in the [Roadmap](#roadmap) section. If you have a suggestion or comment, please open an [Issue](../../issues) and label it as such, it would be much appreciated!

## Installing SDK and Mods

First, go to the [Releases](../../releases/latest) page and download the ZIP file from the latest version there. Inside should be a few things that you will need.

Next, you will need to locate your file directory for Insaniquarium. There are two methods for doing this depending on if you are using the Retail or Steam copy of the game:

<details>
<summary><b>Retail</b><hr></summary>
<blockquote>

You can right-click on the shortcut in your Start menu or Desktop and select "*Open file location*", or navigate to its default install location: "**C:\Program Files (x86)\Insaniquarium**".

For installing mods, you will need to navigate to another folder to drop those: "**C:\ProgramData\PopCap Games\Insaniquarium**". More info is below.
</blockquote>
</details>

<details>
<summary><b>Steam</b><hr></summary>
<blockquote>

The Steam copy of the game is a bit unique, the game is actually extracted and ran in another folder. Because of this DRM measure, you will need to navigate to that folder.

On Windows: "**C:\ProgramData\PopCap Games\Insaniquarium**"

Through Proton (Linux), it *may* be here: "**~/.steam/debian-installation/steamapps/compatdata/3320/pfx/drive_c/ProgramData/PopCap Games/Insaniquarium**" (or a similar path depending on where your Steam folder is set up, but everything after "**compatdata**" should match).

Also, if you are using Proton (Linux), make sure to complete the [extra step required](#proton---modifying-launch-settings) as well.
</blockquote>
</details>
<br>

Once you found your folder, you will simply need to extract the files included from the ZIP file in there. The SDK part is done!

For mods, you will need to add them in this location (or if following the Retail steps, the aforementioned "mods" folder). Create a folder named "**Algae**" if it does not exist yet, and then in there, create another one named "**mods**". This is where you will place all of your Algae mods.

## Proton - Modifying Launch Settings

If you are playing the game through Proton, there is just one extra step you will need to do:

1) Right-click on the game in your Library and select "*Properties...*"
2) In the Launch Options box, paste these arguments there: `WINEDLLOVERRIDES="winmm=n,b" %command%`

The reason for this requirement is because on Windows, applications search their immediate folder for certain specific DLL's (like "**winmm.dll**") before checking system folders for them, while on Proton, it seems to work the other way around. This command ensures the game will check around itself first ("native" DLL's), before looking for the "built-in" ones.

## Building

The project uses Visual Studio 2022. More info in the future on how to build, but it should be as straightforward as this:
  * Build the solution in the "Release - Win32" configuration (or Debug if you need to, y'know, debug anything).
  * Take the output DLLs (**winmm.dll**, **AlgaeSDK.dll**) and drop them in the same folder as your Insaniquarium installation.
  * Done!

If you are looking to build the project on Linux or Mac, I will get around to looking into a more portable solution eventually!

## Writing your own mods

Information will eventually be provided in the Wiki, including setup and documentation.

## Roadmap

Currently (as of 2026/11/05), Algae is severely under-developed, with just a few hooks and some basic functions provided. However, despite having limited time to work on it, there is some progress, and I decided that it is far enough along that I'm happy with publishing it. Please follow along as I continue working on it!

- [x] Build out a proper logging system
- [x] Fix folder structure and naming conventions (unhappy with it at the moment)
- [x] Build out std::string interop (turns out we can't just pass a 2022 std::string to 2005, need to figure out a solution)
- [ ] Implement config file ini (kinda like Unity Doorstop's)
- [x] Identify Steam and non-Steam builds and adjust addressing according to each version
  - Thankfully they're the same, Steam just has an extra DRM step we can work around
- [ ] Work on an SDK versioning scheme I actually like
- [ ] Add more event hooks to the SDK
- [ ] Add a resource overriding system (add your own assets without overwriting game files)
- [ ] Add an Algae mod menu on the main menu
- [ ] WinXP (or some baseline OS) compatibility?
- [ ] Adding new game object types (fish? aliens? items?)

## AI Disclosure

This project is **not** maintained by, created for, MCP-connected with, or otherwise supported by generative AI, and does not accept contributions generated significantly by an LLM. Any works you see in this project are written by a human being first and foremost, and will remain that way. Doing research, writing your own *personal* tools, following examples, or verifying your work with an AI model is totally acceptable.

I am not a fully anti-AI person, but I seek to work on projects with an intential focus on its design, and throwing out a prompt and some tokens does not constitute intentionality to me. I also do not stand for licensing and publishing works made largely by an AI model without the assurance that its training data is ethically sourced (and AFAIK there are no good ones yet, so it's a moot point).

Note that **this can change** in the future, but will be fully disclosed if anything happens (I'm open to suggestions and ideas). Rest assured though, that this project was made by a person who still likes making things themselves, even if it takes longer. <3

## Dependencies

Dependencies will be located in the "deps" folder.

Currently, only [MinHook](https://github.com/TsudaKageyu/minhook) is used, as it's an incredibly useful tool for hooking into processes and building callbacks. I don't think any of this would be possible without it (or it would have taken much longer).
