/***************************************************************************
 *   Copyright (c) 2017 Abdullah Tahiri <abdullah.tahiri.yo@gmail.com>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "ExceptionFactory.h"

using namespace Base;

ExceptionFactory* ExceptionFactory::_pcSingleton = NULL;

ExceptionFactory& ExceptionFactory::Instance(void)
{
    if (_pcSingleton == NULL)
        _pcSingleton = new ExceptionFactory;
    return *_pcSingleton;
}

void ExceptionFactory::Destruct (void)
{
    if (_pcSingleton != 0)
        delete _pcSingleton;
    _pcSingleton = 0;
}

void ExceptionFactory::raiseException (const ExceptionInfo& info) const
{
    if(this->CanProduce(info.exceptionname.c_str())) {

      std::map<const std::string, AbstractProducer*>::const_iterator pProd;

      pProd = _mpcProducers.find(info.exceptionname.c_str());
      if (pProd != _mpcProducers.end())
          static_cast<AbstractExceptionProducer *>(pProd->second)->raiseException(info);
    }
}

