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

#ifndef _TransferFunction1DRaw_h_
#define _TransferFunction1DRaw_h_

//#include <co/dataIStream.h>
//#include <co/dataOStream.h>

//#include <livre/core/api.h>
//#include <livre/core/types.h>
//#include <livre/core/mathTypes
#include <livre/core/render/TransferFunction1D.h>

namespace livre
{

/**
 * The TransferFunction1DRaw class holds the color and transparency for an RGBA 1 dimensional Transfer Function ( TF ).
 * The data type can be templated by parameter T.
 */
class TransferFunction1DRaw: public TransferFunction1D
{
public:

    /**
     * Create the transfer function with default parameters.
     */
    TransferFunction1DRaw() { reset(); }

    /**
     * Create a transfer function.
     * @param size The number of samples in the transfer function.
     */
    explicit TransferFunction1DRaw( const uint32_t size, const SamplePointsType type = UINT8, const uint8_t nChannels = 4u )
        :  TransferFunction1D( size, type, nChannels )
    {}

    /**
     * Load transfer function from an ASCII "1dt" file. The content of the file
     * consists of a first line with the number of sample points in the transfer
     * function and their format, and then all the values in 'R G B A' format.
     * Currently both float [0.0f, 1.0f] and 8-bit unsigned integers [0, 255]
     * values are supported. If the format is unspecified, float is used.
     * If the file extension or format is not supported or the file could not be
     * opened, a default transfer function is generated.
     * @param file Path to the transfer function file.
     */
    //explicit TransferFunction1DRaw( const std::string& file ) { createTfFromFile_( file ); }

    /**
     * Copy a transfer function.
     * @param tf The transfer function to be copied.
     */
    explicit TransferFunction1DRaw( const TransferFunction1DRaw& tf )
        : TransferFunction1D( tf )
    {}

    /**
     * Create a transfer function.
     * @param rgba A std::vector with samples of the transfer function.
     */
    explicit TransferFunction1DRaw( const UInt8Vector& data, const SamplePointsType type = UINT8, const uint8_t nChannels = 4u )
        : TransferFunction1D( data, type, nChannels )
    {}

    /*TransferFunction1DRaw& operator=( const TransferFunction1DRaw& rhs )
    {
        if( this == &rhs )
            return *this;

        _data = rhs._data;

        return *this;
    }*/

   /**
    * Resets the transfer function with default parameters.
    */
    LIVRECORE_API void reset() final;

private:

    LIVRECORE_API void createCustomTF_( const uint32_t size );
    LIVRECORE_API void createTfFromFile_( const std::string& file );
};

}
#endif // __TransferFunction1DRaw_h_
