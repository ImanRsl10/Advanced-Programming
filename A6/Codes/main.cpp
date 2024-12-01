#include "mission_system.hpp"
#include "process_cmd.hpp"

int main()
{
    Mission_System system;
    process_command(system);
    return 0;
}