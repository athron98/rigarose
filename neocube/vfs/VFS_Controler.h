/**************************************************
*           ----- VFS_Controler -----            *
**************************************************
* Utilisation de la TriggerVFS.dll DLL           *
*                           By JC_Master - 2007  *
**************************************************
*         USE GNU GENERAL PUBLIC LICENSE         *
**************************************************/

#ifndef VFS_CONTROLER_HEADER
	#define VFS_CONTROLER_HEADER

	#include <vector>
	#include <string>
	#include <exception>
	#include <windows.h>

	//Controler de la DLL
	class VFS_Controler
	{
		public:
			//Constructeur
			VFS_Controler();
			//Destructeur
			virtual ~VFS_Controler();

			//Type FileInfo
			struct FileInfo
			{
				uint32_t attribute;
				uint32_t checksum;
			};

			//Type File
			class File
			{
					public:
						//Destructeur
						virtual ~File();

						//Fonctions VFS
						bool         IsOpen();
						unsigned int Read(void* buffer, size_t size, size_t count);
						std::string  ReadAll();
						unsigned int Seek(long int offset,int origin);
						unsigned int Tell();
						bool         Eof();
						unsigned int GetSize();
						bool         CopyFile(const std::string& localpath);
						bool         Close();
					private:
						//Constructeur
						File(unsigned int filehandle, VFS_Controler& parent);

						//FileHandle
						uint32_t _FileHandle;

						//Parent
						VFS_Controler& _Parent;

						//Peut créer des instances de File
						friend class VFS_Controler;
			};

			//Fonctions VFS
			bool                     IsOpen();
			bool                     OpenVFS(const std::string& path = "data.idx", const std::string& mode = "r+");
			bool                     CloseVFS();
			unsigned int             GetError();
			unsigned int             GetVfsCount();
			std::vector<std::string> GetVfsNames();
			bool                     AddVfs(const std::string& vfsfile);//Don't work
			unsigned int             ClearBlankAll(const std::string& vfsfile);//Don't work
			unsigned int             GetFileCount(const std::string& vfsfile);
			std::vector<std::string> GetFileNames(const std::string& vfspath);
			FileInfo                 GetFileInfo(const std::string& vfspath);
			bool                     SetFileInfo(const std::string& vfspath, const FileInfo& info);
			unsigned int             FileExists(const std::string& vfspath);
			unsigned int             FileExistsInVfs(const std::string& vfspath);
			unsigned int             ComputeCrc(const std::string& vfspath);
			File                     OpenFile(const std::string& vfspath);
			unsigned int             RemoveFile(const std::string& vfspath);
			bool                     AddFile(const std::string& insertvfs, const std::string& localpath, const std::string& vfspath, const unsigned int checksum = 0xFF);
			bool                     CopyFile(const std::string& vfspath, const std::string& localpath);
			unsigned int             TestFile(const std::string& vfspath);
			unsigned int             GetFileLength(const std::string& vfspath);
			unsigned int             GetTotFileCount();
			unsigned int             GetCurVersion();
			unsigned int             SetCurVersion(unsigned int curversion);
			unsigned int             GetStdVersion();
			unsigned int             SetStdVersion(unsigned int stdversion);

			//Exceptions
			class VFS_Exception : public std::exception
			{
				public:
					VFS_Exception(std::string Msg);
					virtual ~VFS_Exception() throw();

					virtual const char* what() const throw();

				private:
					std::string _Msg;
			};

		private:
			//Typedef des fonctions VFS
			typedef uint32_t (__stdcall *VFST_OpenVFS)         (const char*, const char*);
			typedef uint32_t (__stdcall *VFST_CloseVFS)        (const uint32_t);
			typedef uint32_t (__stdcall *VFST_GetError)        ();
			typedef uint32_t (__stdcall *VFST_GetVfsCount)     (const uint32_t);
			typedef uint32_t (__stdcall *VFST_GetVfsNames)     (const uint32_t, char*[], uint32_t, uint32_t);
			typedef uint32_t (__stdcall *VFST_AddVfs)          (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_ClearBlankAll)   (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_GetFileCount)    (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_GetFileNames)    (const uint32_t, const char*, char*[], uint32_t, uint32_t);
			typedef uint32_t (__stdcall *VFST_GetFileInfo)     (const uint32_t, const char*, FileInfo*, const uint32_t);
			typedef uint32_t (__stdcall *VFST_SetFileInfo)     (const uint32_t, const char*, const FileInfo*);
			typedef uint32_t (__stdcall *VFST_FileExists)      (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_FileExistsInVfs) (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_ComputeCrc)      (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_OpenFile)        (const char*, const uint32_t);
			typedef uint32_t (__stdcall *VFST_RemoveFile)      (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_Read)            (void*, uint32_t, uint32_t, uint32_t);
			typedef uint32_t (__stdcall *VFST_Seek)            (uint32_t, uint32_t, uint32_t);
			typedef uint32_t (__stdcall *VFST_Tell)            (uint32_t);
			typedef uint32_t (__stdcall *VFST_Eof)             (uint32_t);
			typedef uint32_t (__stdcall *VFST_GetSize)         (const uint32_t);
			typedef uint32_t (__stdcall *VFST_GetFileLength)   (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_TestFile)        (const uint32_t, const char*);
			typedef uint32_t (__stdcall *VFST_CloseFile)       (const uint32_t);
			typedef uint64_t (__stdcall *VFST_AddFile)         (const uint32_t, const char*, const char*, const char*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
			typedef uint32_t (__stdcall *VFST_GetTotFileCount) (const uint32_t);
			typedef uint32_t (__stdcall *VFST_GetCurVersion)   (const uint32_t);
			typedef uint32_t (__stdcall *VFST_SetCurVersion)   (const uint32_t, const uint32_t);
			typedef uint32_t (__stdcall *VFST_GetStdVersion)   (const uint32_t);
			typedef uint32_t (__stdcall *VFST_SetStdVersion)   (const uint32_t, const uint32_t);

			//Fonctions VFS (Protection contre d'éventuels problème de mémoire)
			uint32_t _OpenVFS         (const char* path, const char* mode);
			uint32_t _CloseVFS        (const uint32_t handle);
			uint16_t _GetError        ();
			uint32_t _GetVfsCount     (const uint32_t handle);
			uint32_t _GetVfsNames     (const uint32_t handle, char** array, const uint32_t vfscount, const uint32_t maxlen);
			uint32_t _AddVfs          (const uint32_t handle, const char* vfsfilename);
			uint32_t _ClearBlankAll   (const uint32_t handle, const char* vfsfilename);
			uint32_t _GetFileCount    (const uint32_t handle, const char* vfsfilename);
			uint32_t _GetFileNames    (const uint32_t handle, const char* name, char** array, const uint32_t vfscount, const uint32_t maxlen);
			uint32_t _GetFileInfo     (const uint32_t handle, const char* vfspath, FileInfo* info, const uint32_t filehandle);
			uint32_t _SetFileInfo     (const uint32_t handle, const char* vfspath, const FileInfo* info);
			uint32_t _FileExists      (const uint32_t handle, const char* vfspath);
			uint32_t _FileExistsInVfs (const uint32_t handle, const char* vfspath);
			uint32_t _ComputeCrc      (const uint32_t handle, const char* vfspath);
			uint32_t _OpenFile        (const char* vfspath, const uint32_t handle);
			uint32_t _RemoveFile      (const uint32_t handle, const char* vfspath);
			uint32_t _Read            (void* buffer, const uint32_t size, const uint32_t count, const uint32_t filehandle);
			uint32_t _Seek            (const uint32_t filehandle, const uint32_t offset, const uint32_t origin);
			uint32_t _Tell            (const uint32_t filehandle);
			uint16_t _Eof             (const uint32_t filehandle);
			uint32_t _GetSize         (const uint32_t filehandle);
			uint32_t _GetFileLength   (const uint32_t handle, const char* vfspath);
			uint32_t _TestFile        (const uint32_t handle, const char* vfspath);
			uint32_t _CloseFile       (const uint32_t filehandle);
			uint32_t _AddFile         (const uint32_t handle, const char* insertvfs, const char* localpath, const char* vfspath, const uint32_t checksum, const uint32_t reserved1, const uint32_t reserved2, const uint32_t reserved3, const uint32_t reserved4);
			uint32_t _GetTotFileCount (const uint32_t handle);
			uint32_t _GetCurVersion   (const uint32_t handle);
			uint32_t _SetCurVersion   (const uint32_t handle, const uint32_t curversion);
			uint32_t _GetStdVersion   (const uint32_t handle);
			uint32_t _SetStdVersion   (const uint32_t handle, const uint32_t stdversion);

			//Disparition d'un fils
			void RemoveFileFromList(File* fils);

			//Lien vers la DLL
			HMODULE _DllHandle;

			//Liens vers les fonctions
			VFST_OpenVFS         _OpenVFS_Ptr;
			VFST_CloseVFS        _CloseVFS_Ptr;
			VFST_GetError        _GetError_Ptr;
			VFST_GetVfsCount     _GetVfsCount_Ptr;
			VFST_GetVfsNames     _GetVfsNames_Ptr;
			VFST_AddVfs          _AddVfs_Ptr;
			VFST_ClearBlankAll   _ClearBlankAll_Ptr;
			VFST_GetFileCount    _GetFileCount_Ptr;
			VFST_GetFileNames    _GetFileNames_Ptr;
			VFST_GetFileInfo     _GetFileInfo_Ptr;
			VFST_SetFileInfo     _SetFileInfo_Ptr;
			VFST_FileExists      _FileExists_Ptr;
			VFST_FileExistsInVfs _FileExistsInVfs_Ptr;
			VFST_ComputeCrc      _ComputeCrc_Ptr;
			VFST_OpenFile        _OpenFile_Ptr;
			VFST_RemoveFile      _RemoveFile_Ptr;
			VFST_Read            _Read_Ptr;
			VFST_Seek            _Seek_Ptr;
			VFST_Tell            _Tell_Ptr;
			VFST_Eof             _Eof_Ptr;
			VFST_GetSize         _GetSize_Ptr;
			VFST_GetFileLength   _GetFileLength_Ptr;
			VFST_TestFile        _TestFile_Ptr;
			VFST_CloseFile       _CloseFile_Ptr;
			VFST_AddFile         _AddFile_Ptr;
			VFST_GetTotFileCount _GetTotFileCount_Ptr;
			VFST_GetCurVersion   _GetCurVersion_Ptr;
			VFST_SetCurVersion   _SetCurVersion_Ptr;
			VFST_GetStdVersion   _GetStdVersion_Ptr;
			VFST_SetStdVersion   _SetStdVersion_Ptr;

			//Handle
			uint32_t _Handle;

			//Partage ses fonctions
			friend class File;

			//Fils
			std::vector<File*> _FileList;
};

#endif
