/* Copyright (c) 2011-2014, EPFL/Blue Brain Project
 *                     Ahmet Bilgili <ahmet.bilgili@epfl.ch>
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

#ifndef _TransferFunction1D_h_
#define _TransferFunction1D_h_

#include <co/dataIStream.h>
#include <co/dataOStream.h>

#include <livre/core/api.h>
#include <livre/core/types.h>
#include <livre/core/data/VolumeInformation.h>

#define TF_NCHANNELS 4u

namespace livre
{

enum SamplePointsType
{
    UINT8,
    FLOAT,
    DEFAULT = FLOAT
};

class TransferFunction1D;
typedef boost::shared_ptr< TransferFunction1D > TransferFunction1DPtr;

/**
 * The TransferFunction1D class holds the color and transparency for an RGBA 1 dimensional Transfer Function ( TF ).
 * The data type can be templated by parameter T.
 */
class TransferFunction1D
{
public:
    /**
     * Create the transfer function with default parameters.
     */
    TransferFunction1D();

    virtual ~TransferFunction1D(){}

    /**
     * Create a transfer function.
     * @param size The number of samples in the transfer function.
     * @param type The type of samples. Currenty supported types are uint8_t and floats.
     * @param nChannels The number of channels. RGBA = 4 channels, RGB = 3 channels, ...
     */
    TransferFunction1D( const uint32_t size, const SamplePointsType type = UINT8, const uint8_t nChannels = 4u );

    /**
     * Copy a transfer function.
     * @param tf The transfer function to be copied.
     */
    explicit TransferFunction1D( const TransferFunction1D& tf )
        : _data( tf._data )
        , _nChannels( tf._nChannels )
        , _type( tf._type )
    {}

    /**
     * Create a transfer function.
     * @param rgba A std::vector with samples of the transfer function.
     */
    explicit TransferFunction1D( const UInt8Vector &data, const SamplePointsType type = UINT8, const uint8_t nChannels = 4u )
        : _data( data )
        , _nChannels( nChannels )
        , _type( type )
    {}

    TransferFunction1D& operator=( const TransferFunction1D& rhs )
    {
        if( this == &rhs )
            return *this;

        _data = rhs._data;
        _type = rhs._type;
        _nChannels = rhs._nChannels;
        return *this;
    }

    /**
     * @return The RGBA data vector. The data array is rgba_[] = { R, G, B, A, R, G, B, A, R ... }.
     */
    UInt8Vector& getData() { return _data; }

    /**
     * @return The RGBA data vector. The data array is rgba_[] = { R, G, B, A, R, G, B, A, R ... }.
     */
    const UInt8Vector& getData() const { return _data; }

    uint32_t getNumChannels() { return _nChannels; }

    /**
     * Resets the transfer function with default parameters.
     */
     LIVRECORE_API virtual void reset() = 0;

protected:

    UInt8Vector _data;
    uint8_t _nChannels;
    SamplePointsType _type;

private:

    friend co::DataOStream& operator<<( co::DataOStream& os, const TransferFunction1DPtr tf )
    {
        return os << tf->getData();
    }

    friend co::DataIStream& operator>>( co::DataIStream& is, TransferFunction1DPtr tf )
    {
        return is >> tf->getData();
    }
};

/*co::DataOStream& operator<<( co::DataOStream& os,
                             const TransferFunction1DPtr tf )
{
    return os << tf->getData();
}

co::DataIStream& operator>>( co::DataIStream& is, TransferFunction1DPtr tf )
{
    return is >> tf->getData();
}*/
}
#endif // _TransferFunction1D_h_
