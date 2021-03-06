<div align="center">

# Anurag's build of dwm

```
 _____     ______     ______     __  __     __     __     __    __    
/\  __-.  /\  __ \   /\  == \   /\ \/ /    /\ \  _ \ \   /\ "-./  \   
\ \ \/\ \ \ \  __ \  \ \  __<   \ \  _"-.  \ \ \/ ".\ \  \ \ \-./\ \  
 \ \____-  \ \_\ \_\  \ \_\ \_\  \ \_\ \_\  \ \__/".~\_\  \ \_\ \ \_\ 
  \/____/   \/_/\/_/   \/_/ /_/   \/_/\/_/   \/_/   \/_/   \/_/  \/_/ 
                                                                      
```

<img src="https://i.imgur.com/15UeQry.png">  
 
![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)
![forthebadge](https://forthebadge.com/images/badges/made-with-crayons.svg)
</div>

## FAQ

> What are the bindings?

This is suckless, mmmbud, the source code is the documentation! Check out [config.h](config.h).

Okay, okay, actually I keep a readme in `larbs.mom` for my whole system, including the binds here.
Press `super+F1` to view it in dwm (zathura is required for that binding).
I haven't kept `man dwm`/`dwm.1` updated though. PRs welcome on that, lol.

## Patches and features

- Clickable statusbar with my build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks).
- scratchpad: Accessible with mod+shift+enter.
- New layouts: bstack, fibonacci, deck, centered master and more. All bound to keys `super+(shift+)t/y/u/i`.
- True fullscreen (`super+f`) and prevents focus shifting.
- Windows can be made sticky (`super+s`).
- stacker: Move windows up the stack manually (`super-K/J`).
- shiftview: Cycle through tags (`super+g/;`).
- vanitygaps: Gaps allowed across all layouts.
- swallow patch: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- Systray Icon support
- Latest fixes directly merged from dwm-git master branch
- Inbuilt Autostart function
- Support for different layouts for each tag
## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the status/info bar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one. Hopefully this fix will be in all libxft soon enough.
# ToDo
* [notify patch](https://dwm.suckless.org/patches/focusonnetactive/)
* [losefullscreen patch](https://raw.githubusercontent.com/bakkeby/patches/master/dwm/dwm-losefullscreen-6.2.diff)
* [window sharing patch](https://raw.githubusercontent.com/bakkeby/patches/master/dwm/dwm-netclientliststacking-6.2.diff)
* [better fullscreen patch](https://raw.githubusercontent.com/bakkeby/patches/master/dwm/dwm-fullscreen-compilation-6.2.diff)
* [better swallow patch](https://raw.githubusercontent.com/bakkeby/patches/master/dwm/dwm-swallow-6.2.diff)
* [rio-like-draw patch](https://raw.githubusercontent.com/bakkeby/patches/master/dwm/dwm-riodraw-6.2.diff)
