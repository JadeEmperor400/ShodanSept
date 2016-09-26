#include "Locations.h"
#include "Panion.h"
#include "windows.h"
#include "EntityNames.h"
//Usb

int main()
{
  //create a miner//Panion
  Panion panion(ent_Panion_Bob);

  //simply run the miner through a few Update calls
  for (int i=0; i<20; ++i)
  { 
    panion.Update();

    Sleep(800);
  }

  //wait for a keypress before exiting
  //PressAnyKeyToContinue();

  return 0;
}