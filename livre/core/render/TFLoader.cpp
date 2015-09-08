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

#include <livre/core/render/TFLoader.h>
#include <livre/core/render/TransferFunction1DRaw.h>
#include <livre/core/render/TransferFunction1DCP.h>

#define DEFAULT_NCHANNELS 4u

namespace livre
{

TFLoader::TFLoader(){}

TransferFunction1DPtr TFLoader::loadFromFile( const std::string& file )
{
    //transferFunction = createDefault2ColorTF();
    TransferFunction1DPtr defaultTF( new TransferFunction1DRaw( 256u ));
    defaultTF->reset();
    if( file.empty( ))
    {
        LBWARN << "Using default transfer function" << std::endl;
        return defaultTF;
    }
    if( file.substr( file.find_last_of(".") + 1 ) != "1dt" )
    {
        LBWARN << "Wrong transfer function file format: " << file
               << ", it must be '.1dt'. Using default transfer function"
               << std::endl;
        return defaultTF;
    }

    std::ifstream ifs( file );
    if( !ifs.is_open( ))
    {
        LBWARN << "The specified transfer function file: " << file
               << ", could not be opened. Using default transfer function"
               << std::endl;
        return defaultTF;
    }

    std::string line, val;
    std::getline( ifs, line );
    const std::string& formatStr = line.substr( line.find(' ') + 1 );

    const SamplePointsType format = formatStr == "uint8" ? UINT8 : DEFAULT;

    const size_t numValues = atoi( line.c_str( )) * DEFAULT_NCHANNELS;
    if( !numValues )
    {
        LBWARN << "Wrong format in transfer function file: " << file
               << ", the number of values must be specified. "
               << "Using default transfer function" << std::endl;
        return defaultTF;
    }

    UInt8Vector data( numValues, 0 );

    size_t i = 0;
    while( ifs >> val && i < numValues )
        data[i++] = atof( val.c_str( ));

    TransferFunction1DPtr tf( new TransferFunction1DRaw( data, format ));

    return tf;
}

}
