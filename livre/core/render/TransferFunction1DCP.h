/* Copyright (c) 2011-2014, EPFL/Blue Brain Project
 *                     Grigori Chevtchenko <grigori.chevtchenko@epfl.ch>
 *
 * This file is part of Livre <https://github.com/BlueBrain/Livre>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _TransferFunction1DCP_h_
#define _TransferFunction1DCP_h_

//#include <co/dataIStream.h>
//#include <co/dataOStream.h>

//#include <livre/core/api.h>
//#include <livre/core/types.h>
//#include <livre/core/mathTypes
#include <livre/core/render/TransferFunction1D.h>

namespace livre
{

/**
 * The TransferFunction1DCP class holds the color curves control points positions . The RGBA values
 * are computed from this information. The data type can be templated by parameter T.
 */
class TransferFunction1DCP : public TransferFunction1D
{
public:

    TransferFunction1DCP();

};

}
#endif // __TransferFunctionCP_h_
