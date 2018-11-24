#ifndef _INJECT_HEADER_GUARD_
#define _INJECT_HEADER_GUARD_

#include "includes.h"

class Inject
{
public:
	Inject();
	~Inject();
	unsigned int pid;
	HANDLE ourProcess;
protected:
	

private:

};


extern Inject* ject;

#endif // !_INJECT_HEADER_GUARD_
