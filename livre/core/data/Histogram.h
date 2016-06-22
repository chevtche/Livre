/* Copyright (c) 2011-2016, EPFL/Blue Brain Project
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

#ifndef _Histogram_h_
#define _Histogram_h_

#include <livre/core/api.h>
#include <livre/core/mathTypes.h>
#include <co/distributable.h> // base class

#include <lexis/render/histogram.h> // base class


namespace livre
{

class Histogram : public co::Distributable< ::lexis::render::Histogram >
{
public:
    /**
     * Constructor. Initializes histogram with 0 values
     */
    LIVRECORE_API Histogram();

    /**
     * Copy the histogram.
     * @param hist The histogram to be copied.
     */
    LIVRECORE_API Histogram( const Histogram& hist );
    LIVRECORE_API Histogram& operator=( const Histogram& rhs );

    /**
     * Computes the addition of two histograms and modifies the object
     * @param histogram is the histogram to add
     * @return the modified histogram
     */
    LIVRECORE_API Histogram& operator+=( const Histogram& histogram );

    /**
     * Queries uniformity of the data. ( If histogram has only one value )
     * @param uniformIndex is set when only one bin has all the data
     * @return true data has only one bin filled.
     */
    LIVRECORE_API bool isDataUniform( size_t& uniformIndex ) const;

    /**
     * @return the index with the minimum value ( if there are multiple indices for
     * min value, the smallest index is returned )
     */
    LIVRECORE_API size_t getMinIndex() const;

    /**
     * @return the index with the maximum value ( if there are multiple indices for
     * max value, the smallest index is returned )
     */
    LIVRECORE_API size_t getMaxIndex() const;
};

/** Outputs the histogram information */
std::ostream& operator<<( std::ostream&, const Histogram& );


}
#endif // _Histogram_h_