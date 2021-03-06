/*
 *   Copyright (C) 2015,2016,2018,2020 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Conf.h"
#include "Log.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

const int BUFFER_SIZE = 500;

enum SECTION {
  SECTION_NONE,
  SECTION_GENERAL,
  SECTION_ID_LOOKUP,
  SECTION_LOG,
  SECTION_YSF_NETWORK,
  SECTION_ICOM_NETWORK,
  SECTION_KENWOOD_NETWORK
};

CConf::CConf(const std::string& file) :
m_file(file),
m_tg(9999U),
m_daemon(false),
m_lookupName(),
m_lookupTime(0U),
m_logDisplayLevel(0U),
m_logFileLevel(0U),
m_logFilePath(),
m_logFileRoot(),
m_ysfPort(0U),
m_ysfDebug(false),
m_icomEnabled(false),
m_icomAddress(),
m_icomTGEnable(0U),
m_icomTGDisable(0U),
m_icomDebug(false),
m_kenwoodEnabled(false),
m_kenwoodAddress(),
m_kenwoodTGEnable(0U),
m_kenwoodTGDisable(0U),
m_kenwoodDebug(false)
{
}

CConf::~CConf()
{
}

bool CConf::read()
{
  FILE* fp = ::fopen(m_file.c_str(), "rt");
  if (fp == NULL) {
    ::fprintf(stderr, "Couldn't open the .ini file - %s\n", m_file.c_str());
    return false;
  }

  SECTION section = SECTION_NONE;

  char buffer[BUFFER_SIZE];
  while (::fgets(buffer, BUFFER_SIZE, fp) != NULL) {
	  if (buffer[0U] == '#')
		  continue;

	  if (buffer[0U] == '[') {
		  if (::strncmp(buffer, "[General]", 9U) == 0)
			  section = SECTION_GENERAL;
		  else if (::strncmp(buffer, "[Id Lookup]", 11U) == 0)
			  section = SECTION_ID_LOOKUP;
		  else if (::strncmp(buffer, "[Log]", 5U) == 0)
			  section = SECTION_LOG;
		  else if (::strncmp(buffer, "[YSF Network]", 13U) == 0)
			  section = SECTION_YSF_NETWORK;
		  else if (::strncmp(buffer, "[Icom Network]", 14U) == 0)
			  section = SECTION_ICOM_NETWORK;
		  else if (::strncmp(buffer, "[Kenwood Network]", 17U) == 0)
			  section = SECTION_KENWOOD_NETWORK;
		  else
			  section = SECTION_NONE;

		  continue;
	  }

	  char* key = ::strtok(buffer, " \t=\r\n");
	  if (key == NULL)
		  continue;

	  char* value = ::strtok(NULL, "\r\n");
	  if (section == SECTION_GENERAL) {
		  if (::strcmp(key, "Daemon") == 0)
			  m_daemon = ::atoi(value) == 1;
		  else if (::strcmp(key, "TG") == 0)
			  m_tg = (unsigned short)::atoi(value);
	  } else if (section == SECTION_ID_LOOKUP) {
		  if (::strcmp(key, "Name") == 0)
			  m_lookupName = value;
		  else if (::strcmp(key, "Time") == 0)
			  m_lookupTime = (unsigned int)::atoi(value);
	  } else if (section == SECTION_LOG) {
		  if (::strcmp(key, "FilePath") == 0)
			  m_logFilePath = value;
		  else if (::strcmp(key, "FileRoot") == 0)
			  m_logFileRoot = value;
		  else if (::strcmp(key, "FileLevel") == 0)
			  m_logFileLevel = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "DisplayLevel") == 0)
			  m_logDisplayLevel = (unsigned int)::atoi(value);
	  } else if (section == SECTION_YSF_NETWORK) {
		  if (::strcmp(key, "Port") == 0)
			  m_ysfPort = (unsigned int)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_ysfDebug = ::atoi(value) == 1;
	  } else if (section == SECTION_ICOM_NETWORK) {
		  if (::strcmp(key, "Enabled") == 0)
			  m_icomEnabled = ::atoi(value) == 1;
		  else if (::strcmp(key, "Address") == 0)
			  m_icomAddress = value;
		  else if (::strcmp(key, "TGEnable") == 0)
			  m_icomTGEnable = (unsigned short)::atoi(value);
		  else if (::strcmp(key, "TGDisable") == 0)
			  m_icomTGDisable = (unsigned short)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_icomDebug = ::atoi(value) == 1;
	  } else if (section == SECTION_KENWOOD_NETWORK) {
		  if (::strcmp(key, "Enabled") == 0)
			  m_kenwoodEnabled = ::atoi(value) == 1;
		  else if (::strcmp(key, "Address") == 0)
			  m_kenwoodAddress = value;
		  else if (::strcmp(key, "TGEnable") == 0)
			  m_kenwoodTGEnable = (unsigned short)::atoi(value);
		  else if (::strcmp(key, "TGDisable") == 0)
			  m_kenwoodTGDisable = (unsigned short)::atoi(value);
		  else if (::strcmp(key, "Debug") == 0)
			  m_kenwoodDebug = ::atoi(value) == 1;
	  }
  }

  ::fclose(fp);

  return true;
}

bool CConf::getDaemon() const
{
	return m_daemon;
}

unsigned short CConf::getTG() const
{
	return m_tg;
}

std::string CConf::getLookupName() const
{
	return m_lookupName;
}

unsigned int CConf::getLookupTime() const
{
	return m_lookupTime;
}

unsigned int CConf::getLogDisplayLevel() const
{
	return m_logDisplayLevel;
}

unsigned int CConf::getLogFileLevel() const
{
	return m_logFileLevel;
}

std::string CConf::getLogFilePath() const
{
  return m_logFilePath;
}

std::string CConf::getLogFileRoot() const
{
  return m_logFileRoot;
}

unsigned int CConf::getYSFPort() const
{
	return m_ysfPort;
}

bool CConf::getYSFDebug() const
{
	return m_ysfDebug;
}

bool CConf::getIcomEnabled() const
{
	return m_icomEnabled;
}

std::string CConf::getIcomAddress() const
{
	return m_icomAddress;
}

unsigned short CConf::getIcomTGEnable() const
{
	return m_icomTGEnable;
}

unsigned short CConf::getIcomTGDisable() const
{
	return m_icomTGDisable;
}

bool CConf::getIcomDebug() const
{
	return m_icomDebug;
}

bool CConf::getKenwoodEnabled() const
{
	return m_kenwoodEnabled;
}

std::string CConf::getKenwoodAddress() const
{
	return m_kenwoodAddress;
}

unsigned short CConf::getKenwoodTGEnable() const
{
	return m_kenwoodTGEnable;
}

unsigned short CConf::getKenwoodTGDisable() const
{
	return m_kenwoodTGDisable;
}

bool CConf::getKenwoodDebug() const
{
	return m_kenwoodDebug;
}
