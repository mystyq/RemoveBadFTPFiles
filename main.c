#include <hal/debug.h>
#include <hal/video.h>
#include <hal/xbox.h>
#include <nxdk/mount.h>
#include <windows.h>

void Remove_Directory(LPCSTR lpPathName)
{
	if (!nxMountDrive('E', "\\Device\\Harddisk0\\Partition1\\"))
	{
		debugPrint("Failed to mount E: drive!\n");
		return;
	}
	if (RemoveDirectory(lpPathName))
	{
		debugPrint("Directory removed successfully\n");
	}
	else
	{
		DWORD error = GetLastError();
		switch (error)
		{
			case ERROR_DIR_NOT_EMPTY:
				debugPrint("The directory is not empty.");
				break;
			case ERROR_PATH_NOT_FOUND:
				debugPrint("The system cannot find the path specified.");
				break;
			default:
				debugPrint("error: %lx\n", error);
		}
	}
}

void Delete_File(LPCSTR lpFileName)
{
	if (!nxMountDrive('E', "\\Device\\Harddisk0\\Partition1\\"))
	{
		debugPrint("Failed to mount E: drive!\n");
		return;
	}
	if (DeleteFile(lpFileName))
	{
		debugPrint("File deleted successfully\n");
	}
	else
	{
		DWORD error = GetLastError();
		switch (error)
		{
			default:
				debugPrint("error: %lx\n", error);
		}
	}
}

int main(void)
{
	VIDEO_MODE xmode;
	void *p = NULL;
	while (XVideoListModes(&xmode, 0, 0, &p)) { }
	XVideoSetMode(xmode.width, xmode.height, xmode.bpp, xmode.refresh);

	// Remove_Directory();
	// Delete_File("E:\\Apps\\hello\\   ");

	XReboot();
	return 0;
}