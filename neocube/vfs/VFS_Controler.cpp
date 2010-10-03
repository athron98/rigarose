/**************************************************
*           ----- VFS_Controler -----            *
**************************************************
* Utilisation de la TriggerVFS.dll DLL           *
*                           By JC_Master - 2007  *
**************************************************
*         USE GNU GENERAL PUBLIC LICENSE         *
**************************************************/
//VC++ ADD, it's needed :s
#include <precompiled.h>
//Files functions
#include <cstdio>
#include <fstream>
//VC++ don't know uintN_t
//Remember you can change that if you use 64b compilation
typedef double             uint64_t;
typedef unsigned long  int uint32_t;
typedef unsigned short int uint16_t;
typedef char               uint8_t;
//Header
#include "VFS_Controler.h"

//Exceptions
VFS_Controler::VFS_Exception::VFS_Exception(std::string Msg)
{
	_Msg = Msg;
}

VFS_Controler::VFS_Exception::~VFS_Exception() throw()
{
}

const char* VFS_Controler::VFS_Exception::what() const throw()
{
	return _Msg.c_str();
}

//Constructeur
VFS_Controler::VFS_Controler()
{
	// ----- Initialisations -----
	_Handle = 0;

	// ----- Chargement de la DLL -----
	_DllHandle = LoadLibrary("TriggerVFS.dll");
	if(!_DllHandle)
		throw VFS_Exception("Impossible de charger la bibliothèque dynamique TriggerVFS.dll");

	// ----- Chargement des fonctions -----
	// OpenVFS
	_OpenVFS_Ptr = reinterpret_cast<VFST_OpenVFS>(GetProcAddress(_DllHandle, "_OpenVFS@8"));
	if (!_OpenVFS_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_OpenVFS@8'");
	//CloseVFS
	_CloseVFS_Ptr = reinterpret_cast<VFST_CloseVFS>(GetProcAddress(_DllHandle, "_CloseVFS@4"));
	if (!_CloseVFS_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_CloseVFS@4'");
	//GetError
	_GetError_Ptr = reinterpret_cast<VFST_GetError>(GetProcAddress(_DllHandle, "_VGetError@0"));
	if (!_GetError_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetError@0'");
	//GetVfsCount
	_GetVfsCount_Ptr = reinterpret_cast<VFST_GetVfsCount>(GetProcAddress(_DllHandle, "_VGetVfsCount@4"));
	if (!_GetVfsCount_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetVfsCount@4'");
	//GetVfsNames
	_GetVfsNames_Ptr = reinterpret_cast<VFST_GetVfsNames>(GetProcAddress(_DllHandle, "_VGetVfsNames@16"));
	if (!_GetVfsNames_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetVfsNames@16'");
	//AddVfs
	_AddVfs_Ptr = reinterpret_cast<VFST_AddVfs>(GetProcAddress(_DllHandle, "_VAddVfs@8"));
	if (!_AddVfs_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VAddVfs@8'");
	//AddVfs
	_ClearBlankAll_Ptr = reinterpret_cast<VFST_ClearBlankAll>(GetProcAddress(_DllHandle, "_VClearBlankAll@8"));
	if (!_ClearBlankAll_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VClearBlankAll@8'");
	//GetFileCount
	_GetFileCount_Ptr = reinterpret_cast<VFST_GetFileCount>(GetProcAddress(_DllHandle, "_VGetFileCount@8"));
	if (!_GetFileCount_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetFileCount@8'");
	//GetFileNames
	_GetFileNames_Ptr = reinterpret_cast<VFST_GetFileNames>(GetProcAddress(_DllHandle, "_VGetFileNames@20"));
	if (!_GetFileNames_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetFileNames@20'");
	//GetFileInfo
	_GetFileInfo_Ptr = reinterpret_cast<VFST_GetFileInfo>(GetProcAddress(_DllHandle, "_VGetFileInfo@16"));
	if (!_GetFileInfo_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetFileInfo@16'");
	//SetFileInfo
	_SetFileInfo_Ptr = reinterpret_cast<VFST_SetFileInfo>(GetProcAddress(_DllHandle, "_VSetFileInfo@12"));
	if (!_SetFileInfo_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VSetFileInfo@12'");
	//FileExists
	_FileExists_Ptr = reinterpret_cast<VFST_FileExists>(GetProcAddress(_DllHandle, "_VFileExists@8"));
	if (!_FileExists_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VFileExists@8'");
	//FileExistsInVfs
	_FileExistsInVfs_Ptr = reinterpret_cast<VFST_FileExistsInVfs>(GetProcAddress(_DllHandle, "_VFileExistsInVfs@8"));
	if (!_FileExistsInVfs_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VFileExistsInVfs@8'");
	//ComputeCrc
	_ComputeCrc_Ptr = reinterpret_cast<VFST_ComputeCrc>(GetProcAddress(_DllHandle, "_ComputeCrc@8"));
	if (!_ComputeCrc_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_ComputeCrc@8'");
	//OpenFile
	_OpenFile_Ptr = reinterpret_cast<VFST_OpenFile>(GetProcAddress(_DllHandle, "_VOpenFile@8"));
	if (!_OpenFile_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VOpenFile@8'");
	//RemoveFile
	_RemoveFile_Ptr = reinterpret_cast<VFST_RemoveFile>(GetProcAddress(_DllHandle, "_VRemoveFile@8"));
	if (!_RemoveFile_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VRemoveFile@8'");
	//Read
	_Read_Ptr = reinterpret_cast<VFST_Read>(GetProcAddress(_DllHandle, "_vfread@16"));
	if (!_Read_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_vfread@16'");
	//Seek
	_Seek_Ptr = reinterpret_cast<VFST_Seek>(GetProcAddress(_DllHandle, "_vfseek@12"));
	if (!_Seek_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_vseek@12'");
	//Tell
	_Tell_Ptr = reinterpret_cast<VFST_Tell>(GetProcAddress(_DllHandle, "_vftell@4"));
	if (!_Tell_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_vftell@4'");
	//Eof
	_Eof_Ptr = reinterpret_cast<VFST_Eof>(GetProcAddress(_DllHandle, "_vfeof@4"));
	if (!_Eof_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_vfeof@4'");
	//GetSize
	_GetSize_Ptr = reinterpret_cast<VFST_GetSize>(GetProcAddress(_DllHandle, "_vfgetsize@4"));
	if (!_GetSize_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_vfgetsize@4'");
	//GetFileLength
	_GetFileLength_Ptr = reinterpret_cast<VFST_GetFileLength>(GetProcAddress(_DllHandle, "_VGetFileLength@8"));
	if (!_GetFileLength_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetFileLength@8'");
	//TestFile
	_TestFile_Ptr = reinterpret_cast<VFST_TestFile>(GetProcAddress(_DllHandle, "_VTestFile@8"));
	if (!_TestFile_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VTestFile@8'");
	//CloseFile
	_CloseFile_Ptr = reinterpret_cast<VFST_CloseFile>(GetProcAddress(_DllHandle, "_VCloseFile@4"));
	if (!_CloseFile_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VCloseFile@4'");
	//AddFile
	_AddFile_Ptr = reinterpret_cast<VFST_AddFile>(GetProcAddress(_DllHandle, "_VAddFile@36"));
	if (!_AddFile_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VAddFile@36'");
	//GetTotFileCount
	_GetTotFileCount_Ptr = reinterpret_cast<VFST_GetTotFileCount>(GetProcAddress(_DllHandle, "_VGetTotFileCount@4"));
	if (!_GetTotFileCount_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetTotFileCount@4'");
	//GetCurVersion
	_GetCurVersion_Ptr = reinterpret_cast<VFST_GetCurVersion>(GetProcAddress(_DllHandle, "_VGetCurVersion@4"));
	if (!_GetCurVersion_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetCurVersion@4'");
	//SetCurVersion
	_SetCurVersion_Ptr = reinterpret_cast<VFST_SetCurVersion>(GetProcAddress(_DllHandle, "_VSetCurVersion@8"));
	if (!_SetCurVersion_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VSetCurVersion@8'");
	//GetStdVersion
	_GetStdVersion_Ptr = reinterpret_cast<VFST_GetStdVersion>(GetProcAddress(_DllHandle, "_VGetStdVersion@4"));
	if (!_GetStdVersion_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VGetStdVersion@4'");
	//SetStdVersion
	_SetStdVersion_Ptr = reinterpret_cast<VFST_SetStdVersion>(GetProcAddress(_DllHandle, "_VSetStdVersion@8"));
	if (!_SetStdVersion_Ptr)
		throw VFS_Exception("Impossible de trouver la fonction '_VSetStdVersion@8'");
}

//Destructeur
VFS_Controler::~VFS_Controler()
{
	if(_DllHandle)
		FreeLibrary(_DllHandle);
	_Handle = 0;
}

// -- PUBLIC FONCTIONS --

//Est ouvert?
bool VFS_Controler::IsOpen()
{
	return _Handle !=0;
}

//Ouverture d'un VFS
bool VFS_Controler::OpenVFS(const std::string& path, const std::string& mode)
{
	int handle = _OpenVFS(path.c_str(), mode.c_str());
	if(handle)
	{
		_Handle = handle;
		return true;
	}
	else
		return false;
}

//Fermeture d'un VFS
bool VFS_Controler::CloseVFS()
{
	//Fermeture des enfants
	for(std::vector<File*>::iterator i = _FileList.begin(); i != _FileList.end(); i++)
		(**i).Close();

	//On vide notre liste
	_FileList.resize(0);

	//Fermeture du VFS
	if(_CloseVFS(_Handle) == 1)
	{
		_Handle = 0;
		return true;
	}
	else
		return false;
}

//Lecture d'une erreure
unsigned int VFS_Controler::GetError()
{
	return _GetError();
}

//Nombre de VFS
unsigned int VFS_Controler::GetVfsCount()
{
	//La fonction retourne NbVFS+1
	return _GetVfsCount(_Handle) - 1;
}

//Listing des VFS
std::vector<std::string> VFS_Controler::GetVfsNames()
{
	//Nombre de Vfs
	unsigned int vfscount = GetVfsCount();

	//Creation du tableau de resultat
	char** c_array = new char*[vfscount];
	for(unsigned int i=0; i < vfscount; i++)
		c_array[i] = new char[255];

	//Lecture des noms
	unsigned int numres = _GetVfsNames(_Handle, c_array, vfscount, 255);

	//Avec gravity on ne sais jamais...
	if(numres > vfscount)
		numres = vfscount;

	//Creation du resultat
	std::vector<std::string> array;
	array.resize(0);
	for(unsigned int i=0; i < numres; i++)
		array.push_back(std::string(c_array[i]));

	//Destruction du tableau
	for(unsigned int i=0; i < vfscount; i++)
		delete[] c_array[i];
	delete[] c_array;

	return array;
}

//Ajout d'un VFS
bool VFS_Controler::AddVfs(const std::string& vfsfilename)
{
	std::ofstream file(vfsfilename.c_str());
	if(!file)
		return false;
	file.close();
	return (bool)_AddVfs(_Handle, vfsfilename.c_str());
}

//Netoyage d'un VFS
unsigned int VFS_Controler::ClearBlankAll(const std::string& vfsfilename)
{
	return (bool)_ClearBlankAll(_Handle, vfsfilename.c_str());
}

//Nombre de fichier
unsigned int VFS_Controler::GetFileCount(const std::string& vfsfilename)
{
	return _GetFileCount(_Handle, vfsfilename.c_str());
}

//Supression d'un fichier
unsigned int VFS_Controler::RemoveFile(const std::string& vfspath)
{
	if(FileExistsInVfs(vfspath))
		return _RemoveFile(_Handle, vfspath.c_str());
	else
		return 0;
}

//Copie du fichier sur le disque
bool VFS_Controler::CopyFile(const std::string& vfspath, const std::string& localpath)
{
	//Ouverture
	File file = OpenFile(vfspath);
	//Copie
	bool res = file.CopyFile(localpath);
	//Fermeture
	file.Close();
	//Fin
	return res;
}

//Teste le fichier
unsigned int VFS_Controler::TestFile(const std::string& vfspath)
{
	return _TestFile(_Handle, vfspath.c_str());
}

//Lecture de la taille d'un fichier
unsigned int VFS_Controler::GetFileLength(const std::string& vfspath)
{
	return _GetFileLength(_Handle, vfspath.c_str());
}

//Listing des fichiers
std::vector<std::string> VFS_Controler::GetFileNames(const std::string& vfsname)
{
	//Nombre de fichiers
	unsigned int filecount = GetFileCount(vfsname);

	//Creation du tableau de resultat
	char** c_array = new char*[filecount];
	for(unsigned int i=0; i < filecount; i++)
		c_array[i] = new char[255];

	//Lecture des noms
	unsigned int numres = _GetFileNames(_Handle, vfsname.c_str(), c_array, filecount, 255);

	//Avec gravity on ne sais jamais...
	if(numres > filecount)
		numres = filecount;

	//Creation du resultat
	std::vector<std::string> array;
	array.resize(0);
	for(unsigned int i=0; i < numres; i++)
		array.push_back(std::string(c_array[i]));

	//Destruction du tableau
	for(unsigned int i=0; i < filecount; i++)
		delete[] c_array[i];
	delete[] c_array;

	return array;
}

//Lecture des informations
VFS_Controler::FileInfo VFS_Controler::GetFileInfo(const std::string& vfspath)
{
	FileInfo info;
	_GetFileInfo(_Handle, vfspath.c_str(), &info, FileExistsInVfs(vfspath.c_str()));
	return info;
}

//Ecriture des informations
bool VFS_Controler::SetFileInfo(const std::string& vfspath, const VFS_Controler::FileInfo& info)
{
	return (bool)_SetFileInfo(_Handle, vfspath.c_str(), &info);
}

//Verifi l'existance
unsigned int VFS_Controler::FileExists(const std::string& vfspath)
{
	return _FileExists(_Handle, vfspath.c_str());
}

//Verifi l'existance
unsigned int VFS_Controler::FileExistsInVfs(const std::string& vfspath)
{
	return _FileExistsInVfs(_Handle, vfspath.c_str());
}

//Calcule le Crc
unsigned int VFS_Controler::ComputeCrc(const std::string& vfspath)
{
	return _ComputeCrc(_Handle, vfspath.c_str());
}

//Ouverture d'un fichier
VFS_Controler::File VFS_Controler::OpenFile(const std::string& vfspath)
{
	//Création de l'enfant
	File file(_OpenFile(vfspath.c_str(), _Handle), *this);
	//Memorisation du lien de parentée
	_FileList.push_back(&file);
	//Renvoi de l'enfant
	return file;
}

//Ajout d'un fichier
bool VFS_Controler::AddFile(const std::string& insertvfs, const std::string& localpath, const std::string& vfspath, const unsigned int checksum)
{
	std::ifstream file(localpath.c_str());
	if(!file)
		return false;
	file.close();
	_AddFile(_Handle, insertvfs.c_str(), localpath.c_str(), vfspath.c_str(), checksum, 0, 0, 0, 0);
	return !(bool)GetError();
}

//Nombre totale de fichier
unsigned int VFS_Controler::GetTotFileCount()
{
	return _GetTotFileCount(_Handle);
}

//Lecture de CurVersion
unsigned int VFS_Controler::GetCurVersion()
{
	return _GetCurVersion(_Handle);
}

//Modification de CurVersion
unsigned int VFS_Controler::SetCurVersion(unsigned int curversion)
{
	return _SetCurVersion(_Handle, curversion);
}

//Lecture de StdVersion
unsigned int VFS_Controler::GetStdVersion()
{
	return _GetStdVersion(_Handle);
}

//Modification de StdVersion
unsigned int VFS_Controler::SetStdVersion(unsigned int curversion)
{
	return _SetStdVersion(_Handle, curversion);
}

// -- FILE'S FONCTIONS PUBLIC --

bool VFS_Controler::File::IsOpen()
{
	return (_FileHandle != 0);
}

//Lecture dans un fichier
unsigned int VFS_Controler::File::Read(void* buffer, size_t size, size_t count)
{
	//Verification du fichier
	if(!IsOpen())
		return 0;
	//Lecture
	return _Parent._Read(buffer, size, count, _FileHandle);
}

//Lecture dans un fichier
std::string VFS_Controler::File::ReadAll()
{
	//Verification du fichier
	if(!IsOpen())
		return "";
	//Memorisation de la position
	long int pos = Tell();
	//Positionement
	Seek(0, SEEK_SET);

	//Lecture
	char* buffer = new char[513];
	std::string FileContent;
	while(!Eof())
	{
		int l = Read(buffer, sizeof(char), 512);
		buffer[l+1] = '\0';
		FileContent += buffer;
	}
	delete buffer;

	//Restauration de la position
	Seek(pos, SEEK_SET);

	//Renvoi du resultat
	return FileContent;
}

//Deplacement dans un fichier
unsigned int VFS_Controler::File::Seek(long int offset, int origin)
{
	//Verification du fichier
	if(!IsOpen())
		return 0;
	//Deplacement
	return _Parent._Seek(_FileHandle, offset, origin);
}

//Lecture de la position dans un fichier
unsigned int VFS_Controler::File::Tell()
{
	//Verification du fichier
	if(!IsOpen())
		return 0;
	//Lecture
	return _Parent._Tell(_FileHandle);
}

//Detection de la fin du fichier
bool VFS_Controler::File::Eof()
{
	//Verification du fichier
	if(!IsOpen())
		return false;
	//Detection
	return (bool)_Parent._Eof(_FileHandle);
}

//Lecture de la taille d'un fichier
unsigned int VFS_Controler::File::GetSize()
{
	//Verification du fichier
	if(!IsOpen())
		return 0;
	return _Parent._GetSize(_FileHandle);
}

bool VFS_Controler::File::CopyFile(const std::string& localpath)
{
	//Verification du fichier
	if(!IsOpen())
		return false;
	//Memorisation de la position
	long int pos = Tell();

	//Positionement
	Seek(0, SEEK_SET);

	//Lecture
	long int size = GetSize();
	char* buffer = new char[size];
	Read(buffer, sizeof(char), size);

	//Ecriture
	std::ofstream File(localpath.c_str());
	if(!File)
	{
		delete buffer;
		return false;
	}
	File.write(buffer, size);
	File.close();

	//Lberation de la mémoire
	delete buffer;

	//Restauration de la position
	Seek(pos, SEEK_SET);

	//Operation réussie
	return true;
}

//Fermeture d'un fichier
bool VFS_Controler::File::Close()
{
	if(IsOpen())
	{
		//Le Parent ferme automatiquement le fichier à sa destruction
		bool res = (bool)_Parent._CloseFile(_FileHandle);
		_FileHandle = 0;
		return res;
	}
	else
		return true;
}

// -- FILE'S PRIVATE FONCTIONS --

//Constructeur
VFS_Controler::File::File(unsigned int filehandle, VFS_Controler& parent)
	:_Parent(parent)
{
	_FileHandle = filehandle;
}

VFS_Controler::File::~File()
{
	//On dit au parent d'oublier l'enfant
	if(_FileHandle != 0)
		_Parent.RemoveFileFromList(this);
	//Fermeture
	Close();
}

// -- PRIVATE FONCTIONS --

//Ouverture d'un VFS
uint32_t VFS_Controler::_OpenVFS(const char* path, const char* mode)
{
	return _OpenVFS_Ptr(path, mode);
}

//Fermeture d'un VFS
uint32_t VFS_Controler::_CloseVFS(const uint32_t handle)
{
	return _CloseVFS_Ptr(handle);
}

//Lecture d'une erreure
uint16_t VFS_Controler::_GetError()
{
	return _GetError_Ptr();
}

//Nombre de VFS
uint32_t VFS_Controler::_GetVfsCount(const uint32_t handle)
{
	return _GetVfsCount_Ptr(handle);
}

//Listing des VFS
uint32_t VFS_Controler::_GetVfsNames(const uint32_t handle, char** array, const uint32_t vfscount, const uint32_t maxlen )
{
	return _GetVfsNames_Ptr(handle, array, vfscount, maxlen);
}

//Ajouter un VFS
uint32_t VFS_Controler::_AddVfs(const uint32_t handle, const char* vfsfilename)
{
	return _AddVfs_Ptr(handle, vfsfilename);
}

//Netoyer un VFS
uint32_t VFS_Controler::_ClearBlankAll(const uint32_t handle, const char* vfsfilename)
{
	return _ClearBlankAll_Ptr(handle, vfsfilename);
}

//Nombre de fichier
uint32_t VFS_Controler::_GetFileCount(const uint32_t handle, const char* vfsfilename)
{
	return _GetFileCount_Ptr(handle, vfsfilename);
}

//Listing des fichiers
uint32_t VFS_Controler::_GetFileNames(const uint32_t handle, const char* name, char** array, uint32_t vfscount, uint32_t maxlen)
{
	return _GetFileNames_Ptr(handle, name, array, vfscount, maxlen);
}


//Lecture des informations
uint32_t VFS_Controler::_GetFileInfo(const uint32_t handle, const char* vfspath, FileInfo* info, uint32_t filehandle)
{
	return _GetFileInfo_Ptr(handle, vfspath, info, filehandle);
}

//Ecriture des informations
uint32_t VFS_Controler::_SetFileInfo(const uint32_t handle, const char* vfspath, const FileInfo* info)
{
	return _SetFileInfo_Ptr(handle, vfspath, info);
}

//Verifi l'existance
uint32_t VFS_Controler::_FileExists(const uint32_t handle, const char* vfspath)
{
	return _FileExists_Ptr(handle, vfspath);
}

//Verifi l'existance
uint32_t VFS_Controler::_FileExistsInVfs(const uint32_t handle, const char* vfspath)
{
	return _FileExistsInVfs_Ptr(handle, vfspath);
}

//Calcule le Crc
uint32_t VFS_Controler::_ComputeCrc(const uint32_t handle, const char* vfspath)
{
	return _ComputeCrc_Ptr(handle, vfspath);
}

//Ouverture d'un fichier
uint32_t VFS_Controler::_OpenFile(const char* vfspath, const uint32_t handle)
{
	return _OpenFile_Ptr(vfspath, handle);
}

//Supression d'un fichier
uint32_t VFS_Controler::_RemoveFile(const uint32_t handle, const char* filename)
{
	return _RemoveFile_Ptr(handle, filename);
}

//Lecture dans un fichier
uint32_t VFS_Controler::_Read(void* buffer, const uint32_t size, const uint32_t count, const uint32_t filehandle)
{
	return _Read_Ptr(buffer, size, count, filehandle);
}

//Deplacement dans un fichier
uint32_t VFS_Controler::_Seek(const uint32_t filehandle, const uint32_t offset, const uint32_t origin)
{
	return _Seek_Ptr(filehandle, offset, origin);
}

//Lecture de la position dans un fichier
uint32_t VFS_Controler::_Tell(const uint32_t filehandle)
{
	return _Tell_Ptr(filehandle);
}

//Detection de la fin du fichier
uint16_t VFS_Controler::_Eof(const uint32_t filehandle)
{
	return _Eof_Ptr(filehandle);
}

//Lecture de la taille d'un fichier
uint32_t VFS_Controler::_TestFile(const uint32_t handle, const char* vfspath)
{
	return _TestFile_Ptr(handle, vfspath);
}

//Lecture de la taille d'un fichier
uint32_t VFS_Controler::_GetSize(const uint32_t filehandle)
{
	return _GetSize_Ptr(filehandle);
}

//Lecture de la taille d'un fichier
uint32_t VFS_Controler::_GetFileLength(const uint32_t handle, const char* vfspath)
{
	return _GetFileLength_Ptr(handle, vfspath);
}

//Fermeture d'un fichier
uint32_t VFS_Controler::_CloseFile(const uint32_t filehandle)
{
	return _CloseFile_Ptr(filehandle);
}

//Ajout d'un fichier
uint32_t VFS_Controler::_AddFile(const uint32_t handle, const char* insertvfs, const char* localpath, const char* vfspath, const uint32_t checksum, const uint32_t reserved1, const uint32_t reserved2, const uint32_t reserved3, const uint32_t reserved4)
{
	return _AddFile_Ptr(handle, insertvfs, localpath, vfspath, checksum, reserved1, reserved2, reserved3, reserved4);
}

//Nombre totale de fichier
uint32_t VFS_Controler::_GetTotFileCount(const uint32_t handle)
{
	return _GetTotFileCount_Ptr(handle);
}

//Lecture de CurVersion
uint32_t VFS_Controler::_GetCurVersion(const uint32_t handle)
{
	return _GetCurVersion_Ptr(handle);
}

//Modification de CurVersion
uint32_t VFS_Controler::_SetCurVersion(const uint32_t handle, const uint32_t curversion)
{
	return _SetCurVersion_Ptr(handle, curversion);
}

//Lecture de StdVersion
uint32_t VFS_Controler::_GetStdVersion(const uint32_t handle)
{
	return _GetCurVersion_Ptr(handle);
}

//Modification de StdVersion
uint32_t VFS_Controler::_SetStdVersion(const uint32_t handle, const uint32_t curversion)
{
	return _SetStdVersion_Ptr(handle, curversion);
}

//Disparition d'un fils
void VFS_Controler::RemoveFileFromList(File* fils)
{
	for(std::vector<File*>::iterator i = _FileList.begin(); i != _FileList.end(); i++)
	{
		//On a retrouver la pointeur
		if(*i == fils)
		{
			//On le retire de la liste
			_FileList.erase(i);
			//On sort de la boucle
			break;
		}
	}
}
