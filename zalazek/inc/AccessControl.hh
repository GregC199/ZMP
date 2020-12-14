#ifndef ACCESSCONTROLL_HH
#define ACCESSCONTROLL_HH

#include <mutex>

class AccessControl {

    std::mutex   _InternalGuard;
    bool         _Changed = false;
    std::mutex  _ExternalGuard;

 public:

   bool IsChanged() const { return _Changed; }

   void MarkChange() { _InternalGuard.lock();  _Changed = true;  _InternalGuard.unlock(); }

   void CancelChange() { _InternalGuard.lock();  _Changed = false;  _InternalGuard.unlock(); }

   void LockAccess() { _ExternalGuard.lock(); }

   void UnlockAccess() { _ExternalGuard.unlock(); }
};




#endif
