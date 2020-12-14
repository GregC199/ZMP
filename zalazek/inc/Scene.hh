#ifndef SCENE_HH
#define SCENE_HH

#include "MobileObj.hh"
#include <string>
#include <map>
#include <iostream>
#include "AccessControl.hh"

using std::shared_ptr;
using std::map;
using std::string;


const char* Cmds4Obj[5] = {
  "Cube  2 2.5 1.1  0 0 0  0 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 1   5 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  10 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  15 0 0  0 0 255\n",
  "Cube  2 2.5 1.1  0 0 2  20 0 0  0 0 255\n"
 };

class GeomObject {

   int _StateIdx = 0;

   const char** _Cmd4StatDesc = nullptr;

 public:

  void SetCmds(const char *CmdsTab[5]) { _Cmd4StatDesc = CmdsTab; }

  const char* GetStateDesc() const
  {
    return _Cmd4StatDesc[_StateIdx];
  }
  bool IncStateIndex() {
    if (_StateIdx >= 4) return false;
    ++_StateIdx;
    return true;
  }
};

typedef map<string, shared_ptr<MobileObj>> Objects_map;


class Scene: public AccessControl{

  string _Name{"Nameless map"};

public:


  Scene(): _Container4Objects(1)
  {
    _Container4Objects[0].SetCmds(Cmds4Obj);
  }


  Scene(string t_name){
    _Name = t_name;
  }

  std::vector<GeomObject>   _Container4Objects;

  const string GetName(){
    return _Name;
  }

  Objects_map _Set_MobileObjs;

  MobileObj* FindObj(const char *sName);

  void AddObj(shared_ptr<MobileObj> &pObj){
    _Set_MobileObjs.insert(std::pair<string, shared_ptr<MobileObj>>(pObj->GetName(), pObj));

    std::cout << "Added object: " << pObj->GetName() << " to scene: "
	      << _Name  << std::endl;
  }
};

#endif
