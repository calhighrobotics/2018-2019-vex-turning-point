#include "speaker.hpp"
#include <API.h>

using namespace speaker;
/*
static const char* mario = "Super Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,"
    "8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,"
    "16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,"
    "16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8p,16g6,16f#6,16f6,16d#6,16p,"
    "16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,"
    "16e6,16p,16c7,16p,16c7,16c7,8p.,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,"
    "16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
static const char* police = "PoliceSiren:d=2,o=5,b=280:"
    "g,c6,g,c6,g,c6,g,c6,g,c6,g,c6,g,c6,g,c6,g,c6,g,c6,g,c6,g,c6";

static const char* rtttl[] = {
    "Super Mario:d=4,o=5,b=100:"
        "16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,"
        "8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
        "8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,"
        "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
        "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,8p.,"
        "8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,"
        "8p,16d#6,8p,16d6,8p,16c6",
    "Super Mario:d=4,o=4,b=100:"
        "16d,16d,32p,8d,16d,8d,8g5,8p,8g,8p,"
        "8g5,16p,8e,16p,8c,16p,8f,8g,16f#,8f,16e.,16c5,16e5,8f5,16d5,8e5,8c5,16a,16b,8g,16p,"
        "8g5,16p,8e,16p,8c,16p,8f,8g,16f#,8f,16e.,16c5,16e5,8f5,16d5,8e5,8c5,16a,16b,8g,16p,"
        "8c,16p,16g,8p,8c5,8f,16p,16c5,16c5,16c5,8f,"
        "8c,16p,16e,8p,16g,16c5,p.,8g,"
        "8c,16p,16g,8p,8c5,8f,16p,16c5,16c5,16c5,8f,"
        "8c,16g#,8p,16a#,8p,16c5",
    NULL
};
static const char* batman = "Batman:d=8,o=5,b=180:"
    "d,d,c#,c#,c,c,c#,c#,d,d,c#,c#,c,c,c#,c#,d,d#,c,c#,c,c,c#,c#,f,p,4f";
static const char* ussr = "USSR National Anthem:d=4,o=5,b=250:"
    "f6, 2a#6, f.6, 8g6, 2a6, d6, d6, 2g6, f.6, 8d#6, 2f6, a#., 8a#, 2c6, c.6,"
    "8d6, 2d#6, d#6, f6, 2g6, a.6, 8a#6, 2c.6, f6, 2d6, c.6, 8a#6, 2c6, a6, f6,"
    "2a#6, a.6, 8g6, 2a6, d6, d6, 2g6, f.6, 8d#6, 2f6, a#., 8a#, 2a#6, a.6, 8g6,"
    "1f6, 1d6, c6, a#6, a6, a#6, 2c.6, f6, 2f.6, 1a#6, a6, g6, f6, g6, 2a.6, d6, 2d6";
static const char* murica = "murica:d=4,o=5,b=100:"
    "8g.,16e,c,e,g,2c6,8e.6,16d6,c6,e,f#,2g,g, e.6,8d6,c6,2b,8a.,16b,c6,c6,g,e,c";

static const char* g_sharp = "g_sharp:d=4,o=7,b=300:"
    "g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,"
    "g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,g#,";
*/
void speaker::init()
{
    speakerInit();
}

void speaker::play()
{
    //puts("speaker play called henlo");
    //speakerPlayRtttl(mario);
    //speakerPlayRtttl(police);
    //speakerPlayArray(rtttl);
    //speakerPlayRtttl(batman);
    //speakerPlayRtttl(ussr);
    //speakerPlayRtttl(murica);
    //speakerPlayRtttl(g_sharp);
}
