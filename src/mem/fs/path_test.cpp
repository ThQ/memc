#include "gtest/gtest.h"
#include "mem/fs/path.hpp"


TEST (mem_fs_path_split, Empty)
{
   std::pair<std::string, std::string> parts = mem::fs::path::split("");
   ASSERT_EQ(parts.first, "");
   ASSERT_EQ(parts.second, "");
}

TEST (mem_fs_path_split, NoFile)
{
   std::pair<std::string, std::string> parts = mem::fs::path::split("/home/thomas/");
   ASSERT_EQ(parts.first, "/home/thomas/");
   ASSERT_EQ(parts.second, "");
}

TEST (mem_fs_path_split, NoDir)
{
   std::pair<std::string, std::string> parts = mem::fs::path::split("test.mem");
   ASSERT_EQ(parts.first, "");
   ASSERT_EQ(parts.second, "test.mem");
}

TEST (mem_fs_path_split, OnlySlash)
{
   std::pair<std::string, std::string> parts = mem::fs::path::split("/");
   ASSERT_EQ(parts.first, "/");
   ASSERT_EQ(parts.second, "");
}

TEST (mem_fs_path_split, DirAndFile)
{
   std::pair<std::string, std::string> parts = mem::fs::path::split("/home/thomas/test.mem");
   ASSERT_EQ(parts.first, "/home/thomas/");
   ASSERT_EQ(parts.second, "test.mem");
}
