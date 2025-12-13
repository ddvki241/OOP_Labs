#include "FileCopier.hpp"
#include <fstream>
#include <filesystem>

using namespace std;

// ===== Конструктор за замовчуванням =====
FileCopier::FileCopier()
{
    sourceFile = "";
    copyFile = "";
    targetDirectory = "";
}

// ===== Конструктор копіювання =====
FileCopier::FileCopier(const FileCopier& other)
{
    sourceFile = other.sourceFile;
    copyFile = other.copyFile;
    targetDirectory = other.targetDirectory;
}

// ===== Конструктор 1 аргумент =====
// Копія створюється як <імʼя>_copy.<розширення>
FileCopier::FileCopier(const string& source)
{
    sourceFile = source;

    // Формуємо імʼя копії
    size_t dot = source.find_last_of('.');
    if (dot != string::npos)
        copyFile = source.substr(0, dot) + "_copy" + source.substr(dot);
    else
        copyFile = source + "_copy";

    targetDirectory = "";
}

// ===== Конструктор 2 аргументи =====
FileCopier::FileCopier(const string& source, const string& copyName)
{
    sourceFile = source;
    copyFile = copyName;
    targetDirectory = "";
}

// ===== Конструктор 3 аргументи =====
FileCopier::FileCopier(const string& source, const string& copyName, const string& directory)
{
    sourceFile = source;
    copyFile = copyName;
    targetDirectory = directory;
}

// ===== Деструктор =====
FileCopier::~FileCopier()
{
    // Можна додати лог для звіту
}

// ===== Метод копіювання =====
bool FileCopier::CopyFile() const
{
    if (!filesystem::exists(sourceFile))
        return false;

    string fullTarget =
        (targetDirectory.empty() ? "" : targetDirectory + "/") + copyFile;

    try
    {
        filesystem::copy_file(
            sourceFile,
            fullTarget,
            filesystem::copy_options::overwrite_existing);

        return true;
    }
    catch (...)
    {
        return false;
    }
}

// ===== Метод визначення розміру =====
long long FileCopier::GetFileSize() const
{
    if (!filesystem::exists(sourceFile))
        return -1;

    return filesystem::file_size(sourceFile);
}
