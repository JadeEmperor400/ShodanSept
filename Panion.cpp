#include "Panion.h"
#include "PanionOwnedStates.h"

Panion::Panion(int id):BaseGameEntity(id),
                     m_Location(shack),
                     m_iGoldCarried(0),
                     m_iMoneyInBank(0),
                     m_iThirst(0),
                     m_iFatigue(0),
                     m_pCurrentState(GoHomeAndSleepTilRested::Instance())
                                                                  
{}

//--------------------------- ChangeState -------------------------------------
//-----------------------------------------------------------------------------
void Panion::ChangeState(State* pNewState)
{
  //make sure both states are both valid before attempting to 
  //call their methods
  assert (m_pCurrentState && pNewState);

  //call the exit method of the existing state
  m_pCurrentState->Exit(this);

  //change state to the new state
  m_pCurrentState = pNewState;

  //call the entry method of the new state
  m_pCurrentState->Enter(this);
}


//-----------------------------------------------------------------------------
void Panion::AddToGoldCarried(const int val)
{
  m_iGoldCarried += val;

  if (m_iGoldCarried < 0) m_iGoldCarried = 0;
}


//-----------------------------------------------------------------------------
void Panion::AddToWealth(const int val)
{
  m_iMoneyInBank += val;

  if (m_iMoneyInBank < 0) m_iMoneyInBank = 0;
}


//-----------------------------------------------------------------------------
bool Panion::Thirsty()const
{
  if (m_iThirst >= ThirstLevel){return true;}

  return false;
}


//-----------------------------------------------------------------------------
void Panion::Update()
{
  m_iThirst += 1;
  
  if (m_pCurrentState)
  {
    m_pCurrentState->Execute(this);
  }
}


//-----------------------------------------------------------------------------
bool Panion::Fatigued()const
{
  if (m_iFatigue > TirednessThreshold)
  {
    return true;
  }

  return false;
}