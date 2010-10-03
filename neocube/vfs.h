/**************************************************
*           ----- VFS_Controler -----            *
**************************************************
* Utilisation de la TriggerVFS.dll DLL           *
*                           By JC_Master - 2007  *
**************************************************
*         USE GNU GENERAL PUBLIC LICENSE         *
**************************************************/

#ifndef VFS_HEADER
	#define VFS_HEADER

	//VC++ don't know uintN_t
	//Remember you can change that if you use 64b compilation
	//typedef double             uint64_t;
	//typedef unsigned long  int uint32_t;
	//typedef unsigned short int uint16_t;
	//typedef char               uint8_t;

	//VFS_Controler
	#include "vfs/VFS_Controler.h"

	class Vfs
	{
		public:
			Vfs(std::string vfsName);
			~Vfs();

			std::string getVfsName();

			VFS_Controler& getVfsCtrl();
		private:
			std::string _vfsName;
			static VFS_Controler _vfsCtrl;
	};

#endif
