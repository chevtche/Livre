
/* Copyright (c) 2011-2016, Maxim Makhinya <maxmah@gmail.com>
 *                          David Steiner  <steiner@ifi.uzh.ch>
 *                          Ahmet Bilgili  <ahmet.bilgili@epfl.ch>
 *                          Stefan.Eilemann@epfl.ch
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

#include <livre/eq/settings/RenderSettings.h>
#include <co/dataIStream.h>
#include <co/dataOStream.h>

namespace livre
{

RenderSettings::RenderSettings()
    :  _depth( 0 )
    ,  _drawAxis( false )
{
    _transferFunction.registerDeserializedCallback( [this]
        { setDirty( DIRTY_TF ); });

    _clipPlanes.registerDeserializedCallback( [this]
        { setDirty( DIRTY_CLIPPLANES ); });

    _clipPlanes.clear();
}

void RenderSettings::resetTransferFunction( )
{
    setTransferFunction( TransferFunction1D( ));
}

void RenderSettings::setTransferFunction( const TransferFunction1D& tf )
{
    _transferFunction = tf;
    setDirty( DIRTY_TF );
}

void RenderSettings::setClipPlanes( const ClipPlanes& clipPlanes )
{
    _clipPlanes = clipPlanes;
    setDirty( DIRTY_CLIPPLANES );
}

/**
 * @param Enable/Disable axis drawing bolean.
 */
void RenderSettings::toggleDrawAxis()
{
    _drawAxis = !_drawAxis;
    setDirty( DIRTY_DRAWAXIS );
}

/**
 * @return Enable/Disable axis drawing bolean.
 */
bool RenderSettings::getDrawAxis() const
{
    return _drawAxis;
}

void RenderSettings::serialize( co::DataOStream& os, const uint64_t dirtyBits )
{
    if( dirtyBits & DIRTY_TF )
        os << _transferFunction;

    if( dirtyBits & DIRTY_DEPTH )
        os << _depth;

    if( dirtyBits & DIRTY_CLIPPLANES )
        os << _clipPlanes;

    if( dirtyBits & DIRTY_DRAWAXIS )
        os << _drawAxis;
}

void RenderSettings::deserialize( co::DataIStream& is, const uint64_t dirtyBits )
{
    if( dirtyBits & DIRTY_TF )
        is >> _transferFunction;

    if( dirtyBits & DIRTY_DEPTH )
        is >> _depth;

    if( dirtyBits & DIRTY_CLIPPLANES )
        is >> _clipPlanes;

    if( dirtyBits & DIRTY_DRAWAXIS )
        is >> _drawAxis;
}

}
