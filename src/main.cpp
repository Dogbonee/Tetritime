#include "StateMachine.h"

int main()
{

    GlobalResources::LoadResources();
    StateMachine sm;

    sm.AddState();
    sm.SwitchState(MENU);
    sm.Run();
    return 0;
}
