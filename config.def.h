/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const double activeopacity   = 1.0f;     /* Window opacity when it's focused (0 <= opacity <= 1) */
static const double inactiveopacity = 1.0f;   /* Window opacity when it's inactive (0 <= opacity <= 1) */
static       Bool bUseOpacity       = True;     /* Starts with opacity on any unfocused windows */
// static const char *fonts[]          = { "Liberation Mono:size=8" };
// static const char dmenufont[]       = "Liberation Mono:size=8";
static const char *fonts[]          = { "IosevkaTerm Nerd Font:size=10" };
static const char dmenufont[]       = "IosevkaTerm Nerd Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyan2[]       = "#00FFFF";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";

static const char *colors[][3]      = {
	/*					fg         bg          border   */
	[SchemeNorm] =	 { col_gray3, col_gray1,  col_gray2 },
	[SchemeSel]  =	 { col_gray4, col_cyan,   col_cyan2 },
	[SchemeWarn] =	 { col_black, col_yellow, col_red },
	[SchemeUrgent]=	 { col_white, col_red,    col_red },
};

static const char *const autostart[] = {
	"xmodmap", "/home/vector/.Xmodmap", NULL,
	"dunst", NULL,
	"slstatus", NULL,
	"picom", NULL,
	// "hsetroot", "-full", "/home/vector/admin/dwm/wallpaper.png", NULL,
	// "feh", "--bg-fill", "/home/vector/admin/dwm/wallpaper.jpg", NULL,
	// "wallset", "--video", "/home/vector/admin/dwm/xasthur.mp3", NULL,
	"/home/vector/bin/wallpaper.sh",
	// "/home/vector/bin/splash.sh",
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,  	  NULL,       "pyside6eg",0,            1,           -1 },
	{ "Sxiv",     NULL,       NULL,       0,            1,           -1 },
	{ "nsxiv",     NULL,       NULL,       0,            1,           -1 },
	{ "vimnotes", NULL,       NULL,       0,            1,           -1 },
	{ "dwmalto",  NULL,       NULL,       0,            1,           -1 },
	{ "termdumpst",  NULL,       NULL,       0,            1,           -1 },
	{ NULL,  NULL,       "dwmalto",       0,            1,           -1 },
	// { "st-256color",     NULL,       NULL,       0,            1,           0.95f,            inactiveopacity,   -1 },
	{ "tmuxmusic", NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
//static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "st", "-e", "tmux", NULL };
// static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "tabbed", "-c", "st", "-w", NULL };
static const char *dwmalto[]  = { "dwm-alto.sh", NULL };
static const char *dwmscreenshot[]  = { "screenshot.sh", NULL };
static const char *incvol[]  = { "inc-volume.sh", NULL };
static const char *decvol[]  = { "dec-volume.sh", NULL };
static const char *switchscrn[]  = { "switch-screen.sh", NULL };
static const char *switchaudio[]  = { "switch_audio_sink.sh", NULL };
static const char *randquote[]  = { "rand-notify", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = switchaudio } },
	{ MODKEY,                       XK_m,      spawn,          {.v = randquote } },
	{ Mod1Mask,                     XK_s,      spawn,          {.v = switchscrn } },
	{ MODKEY,                       XK_o,      spawn,          {.v = dwmalto } },
	{ 0,                            XK_Print,  spawn,          {.v = dwmscreenshot } },
	{ MODKEY,                       XK_bracketright,      spawn,          {.v = incvol } },
	{ MODKEY,                       XK_bracketleft,      spawn,          {.v = decvol } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	// { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_a,      toggleopacity,  {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_j,      moveresize,     {.v = "0x 75y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_k,      moveresize,     {.v = "0x -75y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_l,      moveresize,     {.v = "75x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_h,      moveresize,     {.v = "-75x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_bracketright,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_bracketleft,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_backslash,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_p,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

