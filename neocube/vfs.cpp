//Headers
#include <precompiled.h>
//Remember you can change that if you use 64b compilation
typedef UINT64 uint64_t;
typedef UINT32 uint32_t;
typedef UINT16 uint16_t;
typedef UINT8  uint8_t;
#include "vfs.h"

VFS_Controler Vfs::_vfsCtrl;

Vfs::Vfs(std::string vfsName)
{
	_vfsName = vfsName;
	if(!_vfsCtrl.IsOpen())
		_vfsCtrl.OpenVFS();
}

Vfs::~Vfs()
{
}

VFS_Controler& Vfs::getVfsCtrl()
{
	return _vfsCtrl;
}

std::string Vfs::getVfsName()
{
	return _vfsName;
}
