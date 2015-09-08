/* Copyright (c) 2011-2015, EPFL/Blue Brain Project
 *                          Ahmet Bilgili <ahmet.bilgili@epfl.ch>
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

#include "TransferFunction1D.h"

#include <co/dataIStream.h>
#include <co/dataOStream.h>

#include <fstream>
#include <iterator>

namespace livre
{

TransferFunction1D::TransferFunction1D()
  : _nChannels( 4u )
  , _type( UINT8 )
{
    _data.reserve( 256u * sizeof( uint8_t ) * _nChannels );
}

TransferFunction1D::TransferFunction1D( const uint32_t size, const SamplePointsType type, const uint8_t nChannels )
  : _nChannels( nChannels )
  , _type( type )
{
    switch ( _type )
    {
        case UINT8:
        {
            _data.reserve( size * sizeof( uint8_t ) * _nChannels );
            break;
        }
        case FLOAT:
        {
            _data.reserve( size * sizeof( float ) * _nChannels );
            break;
        }
        default:
        {
            //By default or for unsupported type reserve for uint8_t samples.
            _data.reserve( size * sizeof( uint8_t ) * _nChannels );
            break;
        }
    }
}

}
