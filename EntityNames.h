#ifndef NAMES_H
#define NAMES_H

#include <string>

enum 
{
  ent_Panion_Bob,

  ent_Elsa
};

inline std::string GetNameOfEntity(int n)
{
  switch(n)
  {
  case ent_Panion_Bob:

    return "Companion Pan";

  case ent_Elsa:
    
    return "Elsa"; 

  default:

    return "UNKNOWN!";
  }
}

#endif
