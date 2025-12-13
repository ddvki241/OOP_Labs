#include "pch.h"
#include "CppUnitTest.h"
#include "../FileCopier.hpp/FileCopier.hpp"
#include "../FileCopier.hpp/FileCopier.cpp"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FileCopierTests
{
    TEST_CLASS(FileCopierTests)
    {
    public:

        // Допоміжна функція для створення файлу
        void CreateFile(const std::string& name, const std::string& content = "")
        {
            std::ofstream f(name);
            f << content;
        }

        TEST_METHOD(TestDefaultConstructor)
        {
            FileCopier fc;

            Assert::AreEqual(std::string(""), fc.GetSource());
            Assert::AreEqual(std::string(""), fc.GetCopyName());
            Assert::AreEqual(std::string(""), fc.GetDirectory());
        }

        TEST_METHOD(TestOneArgConstructor)
        {
            FileCopier fc("test.txt");

            Assert::AreEqual(std::string("test.txt"), fc.GetSource());
            Assert::AreEqual(std::string("test_copy.txt"), fc.GetCopyName());
        }

        TEST_METHOD(TestTwoArgConstructor)
        {
            FileCopier fc("a.txt", "b.txt");

            Assert::AreEqual(std::string("a.txt"), fc.GetSource());
            Assert::AreEqual(std::string("b.txt"), fc.GetCopyName());
        }

        TEST_METHOD(TestThreeArgConstructor)
        {
            FileCopier fc("a.txt", "b.txt", "folder");

            Assert::AreEqual(std::string("a.txt"), fc.GetSource());
            Assert::AreEqual(std::string("b.txt"), fc.GetCopyName());
            Assert::AreEqual(std::string("folder"), fc.GetDirectory());
        }

        TEST_METHOD(TestCopyConstructor)
        {
            FileCopier original("x.txt", "y.txt", "dir");
            FileCopier copy(original);

            Assert::AreEqual(std::string("x.txt"), copy.GetSource());
            Assert::AreEqual(std::string("y.txt"), copy.GetCopyName());
            Assert::AreEqual(std::string("dir"), copy.GetDirectory());
        }

        TEST_METHOD(TestGetFileSize)
        {
            CreateFile("size_test.txt", "Hello!");

            FileCopier fc("size_test.txt");

            Assert::AreEqual(6LL, fc.GetFileSize());
        }

        TEST_METHOD(TestGetFileSizeNonexistent)
        {
            FileCopier fc("no_such_file.txt");

            Assert::AreEqual(-1LL, fc.GetFileSize());
        }

        TEST_METHOD(TestCopyFileSuccess)
        {
            CreateFile("orig.txt", "DATA123");

            FileCopier fc("orig.txt", "copy.txt");

            Assert::IsTrue(fc.CopyFile());
            Assert::IsTrue(std::filesystem::exists("copy.txt"));
        }

        TEST_METHOD(TestCopyFileFail_NoSource)
        {
            FileCopier fc("missing.txt", "out.txt");

            Assert::IsFalse(fc.CopyFile());
        }

        TEST_METHOD(TestCopyFileToDirectory)
        {
            // Створимо директорію
            std::filesystem::create_directory("copies");

            CreateFile("doc.txt", "ABC");

            FileCopier fc("doc.txt", "doc_copy.txt", "copies");

            Assert::IsTrue(fc.CopyFile());
            Assert::IsTrue(std::filesystem::exists("copies/doc_copy.txt"));
        }
    };
}

