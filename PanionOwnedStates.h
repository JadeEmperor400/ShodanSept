#ifndef PANION_OWNED_STATES_H
#define PANION_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   PanionOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Panion class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "State.h"


class Panion;


//------------------------------------------------------------------------
//
//  In this state the panion will walk to a goldmine and pick up a nugget
//  of gold. If the panion already has a nugget of gold he'll change state
//  to VisitBankAndDepositGold. If he gets thirsty he'll change state
//  to QuenchThirst
//------------------------------------------------------------------------
class EnterMineAndDigForNugget : public State
{
private:

  EnterMineAndDigForNugget(){}

  //copy ctor and assignment should be private
  EnterMineAndDigForNugget(const EnterMineAndDigForNugget&);
  EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&);

public:

  //this is a singleton
  static EnterMineAndDigForNugget* Instance();
  
  virtual void Enter(Panion* panion);

  virtual void Execute(Panion* panion);

  virtual void Exit(Panion* panion);
};

//------------------------------------------------------------------------
//
//  Entity will go to a bank and deposit any nuggets he is carrying. If the 
//  panion is subsequently wealthy enough he'll walk home, otherwise he'll
//  keep going to get more gold
//------------------------------------------------------------------------
class VisitBankAndDepositGold : public State
{
private:

  VisitBankAndDepositGold(){}

  //copy ctor and assignment should be private
  VisitBankAndDepositGold(const VisitBankAndDepositGold&);
  VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&);
  
public:

  //this is a singleton
  static VisitBankAndDepositGold* Instance();

  virtual void Enter(Panion* panion);

  virtual void Execute(Panion* panion);

  virtual void Exit(Panion* panion);
};


//------------------------------------------------------------------------
//
//  panion will go home and sleep until his fatigue is decreased
//  sufficiently
//------------------------------------------------------------------------
class GoHomeAndSleepTilRested : public State
{
private:

  GoHomeAndSleepTilRested(){}

    //copy ctor and assignment should be private
  GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&);
  GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&);

public:

  //this is a singleton
  static GoHomeAndSleepTilRested* Instance();

  virtual void Enter(Panion* panion);

  virtual void Execute(Panion* panion);

  virtual void Exit(Panion* panion);
};


//------------------------------------------------------------------------
//
//------------------------------------------------------------------------
class QuenchThirst : public State
{
private:
  
  QuenchThirst(){}

  //copy ctor and assignment should be private
  QuenchThirst(const QuenchThirst&);
  QuenchThirst& operator=(const QuenchThirst&);

public:

  //this is a singleton
  static QuenchThirst* Instance();

  virtual void Enter(Panion* panion);

  virtual void Execute(Panion* panion);

  virtual void Exit(Panion* panion);
};





#endif