#include "Panion.h"
#include "PanionOwnedStates.h"

Panion::Panion(int id):BaseGameEntity(id),
                     m_Location(combat),
                     m_ipHP(0),
                     m_icomHP(0),
                     m_idanger(0),
                     m_pCurrentState(aggro::Instance())
                                                                  
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
void Panion::DangerRise(const int val)
{
  m_idanger += val;

  if (m_idanger < 0) m_idanger = 0;
}


//-----------------------------------------------------------------------------
void Panion::PlayerDamageCheck(const int val)
{
  m_ipHP += val;

  if (m_ipHP < 0) m_ipHP = 0;
}
void Panion::CompDamageCheck(const int val)
{
  m_icomHP += val;

  if (m_icomHP < 0) m_icomHP = 0;
}


//-----------------------------------------------------------------------------
/*bool Panion::Thirsty()const
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
}*/

