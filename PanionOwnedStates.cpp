#include "PanionOwnedStates.h"
#include "State.h"
#include "Panion.h"
#include "Locations.h"
//#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

//define this to output to a file
#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif





//--------------------------------------methods for EnterMineAndDigForNugget

EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
  static EnterMineAndDigForNugget instance;

  return &instance;
}

void EnterMineAndDigForNugget::Enter(Panion* pPanion)
{
  //if the Panion is not already located at the goldmine, he must
  //change location to the gold mine
  if (pPanion->Location() != goldmine)
  {
    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Walkin' to the goldmine";

    pPanion->ChangeLocation(goldmine);
  }
}


void EnterMineAndDigForNugget::Execute(Panion* pPanion)
{  
  //the Panion digs for gold until he is carrying in excess of MaxNuggets. 
  //If he gets thirsty during his digging he packs up work for a while and 
  //changes state to go to the saloon for a whiskey.
  pPanion->AddToGoldCarried(1);

  pPanion->IncreaseFatigue();

  //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Pickin' up a nugget";

  //if enough gold mined, go and put it in the bank
  if (pPanion->PocketsFull())
  {
    pPanion->ChangeState(VisitBankAndDepositGold::Instance());
  }

  if (pPanion->Thirsty())
  {
    pPanion->ChangeState(QuenchThirst::Instance());
  }
}


void EnterMineAndDigForNugget::Exit(Panion* pPanion)
{
  //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " 
       << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}



//----------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
  static VisitBankAndDepositGold instance;

  return &instance;
}


void VisitBankAndDepositGold::Enter(Panion* pPanion)
{  
  //on entry the Panion makes sure he is located at the bank
  if (pPanion->Location() != bank)
  {
    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Goin' to the bank. Yes siree";

    pPanion->ChangeLocation(bank);
  }
}


void VisitBankAndDepositGold::Execute(Panion* pPanion)
{

  //deposit the gold
  pPanion->AddToWealth(pPanion->GoldCarried());
    
  pPanion->SetGoldCarried(0);

  //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " 
       << "Depositing gold. Total savings now: "<< pPanion->Wealth();

  //wealthy enough to have a well earned rest?
  if (pPanion->Wealth() >= ComfortLevel)
  {
    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " 
         << "WooHoo! Rich enough for now. Back home to mah li'lle lady";
      
    pPanion->ChangeState(GoHomeAndSleepTilRested::Instance());      
  }

  //otherwise get more gold
  else 
  {
    pPanion->ChangeState(EnterMineAndDigForNugget::Instance());
  }
}


void VisitBankAndDepositGold::Exit(Panion* pPanion)
{
  //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Leavin' the bank";
}


//----------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
  static GoHomeAndSleepTilRested instance;

  return &instance;
}

void GoHomeAndSleepTilRested::Enter(Panion* pPanion)
{
  if (pPanion->Location() != shack)
  {
    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Walkin' home";

    pPanion->ChangeLocation(shack); 
  }
}

void GoHomeAndSleepTilRested::Execute(Panion* pPanion)
{ 
  //if Panion is not fatigued start to dig for nuggets again.
  if (!pPanion->Fatigued())
  {
    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY); 
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " 
          << "What a God darn fantastic nap! Time to find more gold";

     pPanion->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else 
  {
    //sleep
    pPanion->DecreaseFatigue();

    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "ZZZZ... ";
  } 
}

void GoHomeAndSleepTilRested::Exit(Panion* pPanion)
{ 
  //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Leaving the house";
}




//------------------------------------------------methods for QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
  static QuenchThirst instance;

  return &instance;
}

void QuenchThirst::Enter(Panion* pPanion)
{
  if (pPanion->Location() != saloon)
  {    
    pPanion->ChangeLocation(saloon);

    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
  }
}

void QuenchThirst::Execute(Panion* pPanion)
{
   if (pPanion->Thirsty())
   {
     pPanion->BuyAndDrinkAWhiskey();

     //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
     cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "That's mighty fine sippin liquer";

     pPanion->ChangeState(EnterMineAndDigForNugget::Instance());
  }

  else 
  {
    //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
    cout << "\nERROR!\nERROR!\nERROR!";
  } 
}

void QuenchThirst::Exit(Panion* pPanion)
{ 
  //SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(pPanion->ID()) << ": " << "Leaving the saloon, feelin' good";
}
