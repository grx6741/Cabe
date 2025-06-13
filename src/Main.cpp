#include "ArgsManager.h"
#include "Event.h"
#include "InputManager.h"

int main(int argc, char **argv)
{
    Cabe::ArgsManager argsMgr(argc, argv);

    Cabe::InputManager inputMgr;
    Cabe::FileManager fileMgr;

    while (1)
    {
        Cabe::EventPayload eventPayload;
        inputMgr.GetEvent(eventPayload); // Blocking

        if (eventPayload.type == Cabe::Event::QUIT)
        {
            // TODO : Check if all files are saved to Disk
            break;
        }

        fileMgr.update(eventPayload);
    }
}