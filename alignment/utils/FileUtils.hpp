#ifndef _BLASR_FILE_UTILS_HPP_
#define _BLASR_FILE_UTILS_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include "sys/fcntl.h"
#include "sys/mman.h"
#include <sys/types.h> // for lseek
#include <unistd.h> // for lseek
#include <stdio.h>

using namespace std;

bool FileExists(string &fileName);

void CriticalOpenRead(string &fileName, ifstream &file, std::ios::openmode mode=std::ios::in);

int OpenRead(string &fileName, ifstream &file, std::ios::openmode mode=std::ios::in);

void CriticalOpenWrite(string &fileName, ofstream &file, std::ios::openmode mode=std::ios::out);

int OpenWrite(string &fileName, ofstream &file, std::ios::openmode mode=std::ios::out);

int CountLinesInFile(string fileName);

#endif
