/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 4;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 4;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono-Medium:size=10",
                                        "Font Awesome 5 Free-Solid:size=10",
                                        "Font Awesome 5 Free-Regular:size=10",
                                        "Font Awesome 5 Brands-Regular:size=10",
                                        "Material Design Icons-Regular:size=12"

};
static char dmenufont[]             = "monospace:size=10";
static const char col_gray1[]       = "#181818";
static const char col_gray2[]       = "#181818";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#FCFCFC";
static const char col_cyan[]        = "#282A36";
static const char *colors[][3]      = {
        /*               fg         bg         border   */
        [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
        [SchemeSel]  = { col_gray4, col_cyan,  col_gray4  },
};

typedef struct {
        const char *name;
        const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
        /* name          cmd  */
        {"spterm",      spcmd1},
        {"spranger",    spcmd2},
};

static const char *const autostart[] = {
        "sh", "-c", "xrdb ${XDG_CONFIG_HOME:-$HOME/.config}/Xresources &", NULL,
        "sh", "-c", "picom --config ~/.config/picom/picom.conf --experimental-backends &", NULL,
        "sh", "-c", "dunst &", NULL,
        "sh", "-c", "xset r rate 300 50 &", NULL,
        "sh", "-c", "nm-applet &", NULL,
        "sh", "-c", "/usr/libexec/polkit-mate-authentication-agent-1 & eval $(gnome-keyring-daemon -s --components=pkcs11,secrets,ssh,gpg)", NULL,
        "sh", "-c", "xclip &", NULL,
    NULL /* terminate it */
};

/* tagging */
static const char *tags[] = { "1: 󰈹","2: 󰔁", "3: 󱃪" , "4: 󱑴","5: 󰪱", "6: 󰅭"  };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
    */

    /* class                                         instance               title                                                               tags mask                        iscentered   isfloating  isterminal  noswallow     monitor          **/
    { "Gimp",                NULL,        NULL,                              1 << 5,             0,           0,        0,         0,        -1 },
    { NULL,                  NULL,        "Microsoft Teams Notification",    0,                  0,           1,        0,         0,        -1 },
    {"Pavucontrol",          NULL,        NULL,                              0,                  1,           1,        0,         0,        -1 },
    {"kdeconnect.daemon",    NULL,        NULL,                              0,                  1,           3,        0,         0,        -1 },
    { TERMCLASS,             NULL,        NULL,                              0,                  0,           0,        1,         0,        -1 },
    { NULL,                  NULL,        "Event Tester",                    0,                  0,           0,        0,         1,        -1 },
    { NULL,                  "spterm",    NULL,                              SPTAG(0),           0,           1,        1,         0,        -1 },
    { NULL,                  "spcalc",    NULL,                              SPTAG(1),           0,           1,        1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
        /* symbol          arrange function */
        { "[T]",           tile },/*Master on left, slaves on right */
        { "[BS]",          bstack },/* Master on top, slaves on bottom */
        { "[FIB]",   spiral },/* Fibonacci spiral */
        { "[DWI]",         dwindle },/* Decreasing in size right and leftward */
        { "[DK]",          deck },/* Master left, slaves in monocle mode right */
        { "[MOC]",         monocle },/* All windows on top of eachother */
        { "[Cm]",    centeredmaster },/* Master in middle, slaves on sides */
        { "[CFm]",  centeredfloatingmaster }, /* Same but master floats */
        { "[Float]",    NULL },/* no layout function means floating behavior */
        {  NULL,           NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
        { MOD,  XK_j,   ACTION##stack,  {.i = INC(+1) } }, \
        { MOD,  XK_k,   ACTION##stack,  {.i = INC(-1) } }, \
        { MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenui", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };
static const char *playernext[] = { "playerctl", "next", NULL};
static const char *playerprevious[] = { "playerctl", "previous", NULL};
static const char *playerpause[] = { "playerctl", "play-pause", NULL};
static const char *playerstop[] = { "playerctl", "stop", NULL};
static const char *spoticli[] = { "spoticli", "m", NULL};
static const char *clipper[] = { "clipmenu", NULL};
#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
        /* modifier                     key        function        argument */
        STACKKEYS(MODKEY,                          focus)
        STACKKEYS(MODKEY|ShiftMask,                push)
        { MODKEY,                       XK_grave,       spawn,  SHCMD("dmenuunicode") },
        TAGKEYS(                        XK_1,           0)
        TAGKEYS(                        XK_2,           1)
        TAGKEYS(                        XK_3,           2)
        TAGKEYS(                        XK_4,           3)
        TAGKEYS(                        XK_5,           4)
        TAGKEYS(                        XK_6,           5)
        { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
        // { MODKEY,                    XK_minus,       spawn,          SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
        // { MODKEY|ShiftMask,          XK_minus,       spawn,          SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
        // { MODKEY,                    XK_equal,       spawn,          SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
        // { MODKEY|ShiftMask,          XK_equal,       spawn,          SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
        { MODKEY,                       XK_BackSpace,   spawn,          SHCMD("sysact") },
        // { MODKEY|ShiftMask,          XK_BackSpace,   spawn,          SHCMD("sysact") },
        { MODKEY,                       XK_Tab,         view,           {0} },
        { MODKEY|ShiftMask,             XK_q,           killclient,     {0} },
        { MODKEY|ShiftMask,             XK_d, spawn,            {.v = clipper}},
        { MODKEY|ShiftMask,             XK_w,           spawn,          SHCMD("picy") },
        // { MODKEY,                    XK_e,           spawn,          SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
        { MODKEY|ShiftMask,             XK_e,           spawn,          SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
        { MODKEY,                       XK_r,           spawn,          SHCMD(TERMINAL " -e ranger") },
        { MODKEY|ShiftMask,             XK_r,           spawn,          SHCMD(TERMINAL " -e htop") },
        { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} }, /* tile */
        { MODKEY|ShiftMask,             XK_t,           setlayout,      {.v = &layouts[1]} }, /* bstack */
        { MODKEY,                       XK_y,           setlayout,      {.v = &layouts[2]} }, /* spiral */
        { MODKEY|ShiftMask,             XK_y,           setlayout,      {.v = &layouts[3]} }, /* dwindle */
        { MODKEY,                       XK_u,           setlayout,      {.v = &layouts[4]} }, /* deck */
        { MODKEY|ShiftMask,             XK_u,           setlayout,      {.v = &layouts[5]} }, /* monocle */
        { MODKEY,                       XK_i,           setlayout,      {.v = &layouts[6]} }, /* centeredmaster */
        { MODKEY|ShiftMask,             XK_i,           setlayout,      {.v = &layouts[7]} }, /* centeredfloatingmaster */
        { MODKEY,                       XK_o,           incnmaster,     {.i = +1 } },
        { MODKEY|ShiftMask,             XK_o,           incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_p,                   spawn,          SHCMD("mpc toggle") },
        { MODKEY|ShiftMask,             XK_p,                   spawn,          SHCMD("mpc pause ; pauseallmpv") },
        { MODKEY,                       XK_bracketleft,         spawn,          SHCMD("mpc seek -10") },
        { MODKEY|ShiftMask,             XK_bracketleft,         spawn,          SHCMD("mpc seek -60") },
        { MODKEY,                       XK_bracketright,        spawn,          SHCMD("mpc seek +10") },
        { MODKEY|ShiftMask,             XK_bracketright,        spawn,          SHCMD("mpc seek +60") },
        { MODKEY,                       XK_backslash,           view,           {0} },
        { MODKEY,                       XK_a,           togglegaps,     {0} },
        { MODKEY|ShiftMask,             XK_a,           defaultgaps,    {0} },
        { MODKEY,                       XK_s,           togglesticky,   {0} },
        { MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_f,           togglefullscr,  {0} },
        { MODKEY|ShiftMask,             XK_f,           setlayout,      {.v = &layouts[8]} },
        { MODKEY,                       XK_Left,                shiftview,      { .i = -1 } },
        // { MODKEY|ShiftMask,          XK_Left,                shifttag,       { .i = -1 } },
        { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_Right,       shiftview,      { .i = 1 } },
        // { MODKEY|ShiftMask,          XK_Right,       shifttag,       { .i = 1 } },
        { MODKEY,                       XK_apostrophe,  togglescratch,  {.ui = 1} },
        { MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_Return,      togglescratch,  {.ui = 0} },
        { MODKEY,                       XK_z,           incrgaps,       {.i = +3 } },
        { MODKEY,                       XK_x,           incrgaps,       {.i = -3 } },
        { MODKEY,                       XK_b,           togglebar,      {0} },
    { MODKEY,                   XK_n,           spawn,          SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
        // { MODKEY|ShiftMask,          XK_n,           spawn,          SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks") },
        { MODKEY,                       XK_m,           spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
        // { MODKEY|ShiftMask,          XK_m,           spawn,          SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
        { MODKEY,                       XK_comma,       spawn,          SHCMD("mpc prev") },
        { MODKEY|ShiftMask,             XK_comma,       spawn,          SHCMD("mpc seek 0%") },
        { MODKEY,                       XK_period,      spawn,          SHCMD("mpc next") },
        { MODKEY|ShiftMask,             XK_period,      spawn,          SHCMD("mpc repeat") },
        { MODKEY|ShiftMask,             XK_c,   spawn,          SHCMD("code") },
        { MODKEY,                       XK_c,   spawn,          SHCMD(TERMINAL " -e nvim") },
        { MODKEY,                       XK_Left,        focusmon,       {.i = -1 } },
        // { MODKEY|ShiftMask,          XK_Left,        tagmon,         {.i = -1 } },
        { MODKEY,                       XK_Right,       focusmon,       {.i = +1 } },
        // { MODKEY|ShiftMask,          XK_Right,       tagmon,         {.i = +1 } },
        { MODKEY,                       XK_Page_Up,     shiftview,      { .i = -1 } },
        { MODKEY|ShiftMask,             XK_Page_Up,     shifttag,       { .i = -1 } },
        { MODKEY,                       XK_Page_Down,   shiftview,      { .i = +1 } },
        { MODKEY|ShiftMask,             XK_Page_Down,   shifttag,       { .i = +1 } },
        { MODKEY,                       XK_F11,         spawn,          SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
        { MODKEY,                       XK_space,       zoom,           {0} },
        { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
        { 0,                            XK_Print,       spawn,          SHCMD("maim ~/Picx/Screenis/pic-full-$(date '+%y%m%d-%H%M-%S').png") },
        { MODKEY,                       XK_Delete,      spawn,          SHCMD("dmenurecord kill") },
        { MODKEY,                       XK_Scroll_Lock, spawn,          SHCMD("killall screenkey || screenkey &") },
        { 0, XF86XK_AudioMute,          spawn,          SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
        { 0, XF86XK_AudioRaiseVolume,   spawn,          SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
        { 0, XF86XK_AudioLowerVolume,   spawn,          SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
        { 0, XF86XK_AudioPlay,          spawn,          {.v = playerpause}},
        { 0, XF86XK_AudioPause,         spawn,          {.v = playerpause}},
        { 0, XF86XK_AudioNext,          spawn,          {.v = playernext}},
        { 0, XF86XK_AudioPrev,          spawn,          {.v = playerprevious}},
        { 0, XF86XK_AudioStop,          spawn,          {.v = playerstop}},
        { 0, XF86XK_Music,              spawn,          {.v = spoticli}},
        { 0, XF86XK_AudioRewind,        spawn,          SHCMD("mpc seek -10") },
        { 0, XF86XK_AudioForward,       spawn,          SHCMD("mpc seek +10") },
        { 0, XF86XK_AudioMedia,         spawn,          SHCMD(TERMINAL " -e ncmpcpp") },
        { 0, XF86XK_AudioMicMute,       spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
        { 0, XF86XK_PowerOff,           spawn,          SHCMD("sysact") },
        { 0, XF86XK_Calculator,         spawn,          SHCMD(TERMINAL " -e bc -l") },
        { 0, XF86XK_Sleep,              spawn,          SHCMD("sudo -A zzz") },
        { 0, XF86XK_WWW,                spawn,          SHCMD("$BROWSER") },
        { 0, XF86XK_DOS,                spawn,          SHCMD(TERMINAL) },
        { 0, XF86XK_ScreenSaver,        spawn,          SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
        { 0, XF86XK_TaskPane,           spawn,          SHCMD(TERMINAL " -e htop") },
        // { 0, XF86XK_Mail,            spawn,          SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
        { 0, XF86XK_Explorer,           spawn,          SHCMD(TERMINAL " -e ranger") },
        { 0, XF86XK_Launch1,            spawn,          SHCMD("xset dpms force off") },
        { 0, XF86XK_TouchpadToggle,     spawn,          SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
        { 0, XF86XK_TouchpadOff,        spawn,          SHCMD("synclient TouchpadOff=1") },
        { 0, XF86XK_TouchpadOn,         spawn,          SHCMD("synclient TouchpadOff=0") },
        { 0, XF86XK_MonBrightnessUp,    spawn,          SHCMD("xbacklight -inc 15") },
        { 0, XF86XK_MonBrightnessDown,  spawn,          SHCMD("xbacklight -dec 15") },


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
        /* click                event mask      button          function        argument */
#ifndef __OpenBSD__
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
        { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
        { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
        { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
        { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
        { ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
        { ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        defaultgaps,    {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkClientWin,         MODKEY,         Button4,        incrgaps,       {.i = +1} },
        { ClkClientWin,         MODKEY,         Button5,        incrgaps,       {.i = -1} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
        { ClkTagBar,            0,              Button4,        shiftview,      {.i = -1} },
        { ClkTagBar,            0,              Button5,        shiftview,      {.i = 1} },
        { ClkRootWin,           0,              Button2,        togglebar,      {0} },
};
