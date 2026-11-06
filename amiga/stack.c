/* A Shell gives 4 KB of stack; libnix's startup sets this much up instead.
 * The AmiCradle Team. GPL 3 or later, like TecnoballZ. */
unsigned long __stack = 512 * 1024;
static const char version[] __attribute__((used)) = "$VER: TecnoballZ 0.93.1 Amiga (06.11.2026)";
