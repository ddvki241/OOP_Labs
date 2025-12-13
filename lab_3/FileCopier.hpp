#pragma once
#include <string>

class FileCopier
{
private:
    std::string sourceFile;
    std::string copyFile;
    std::string targetDirectory;

public:
    // --- Конструктори ---
    FileCopier(); // за замовчуванням
    FileCopier(const std::string& source); // з 1 аргументом
    FileCopier(const std::string& source, const std::string& copyName); // 2 аргументи
    FileCopier(const std::string& source, const std::string& copyName, const std::string& directory); // 3

    // --- Конструктор копіювання ---
    FileCopier(const FileCopier& other);

    // --- Деструктор ---
    ~FileCopier();

    // --- Методи ---
    bool CopyFile() const;
    long long GetFileSize() const;

    // --- Допоміжні методи ---
    std::string GetSource() const { return sourceFile; }
    std::string GetCopyName() const { return copyFile; }
    std::string GetDirectory() const { return targetDirectory; }
};
