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

#include <livre/core/Render/GLSLShaders.h>
#include <livre/core/Render/RenderBrick.h>
#include <livre/core/Render/Frustum.h>
#include <livre/core/Render/TransferFunction1D.h>
#include <livre/core/Data/LODNode.h>
#include <livre/core/Maths/Maths.h>
#include <livre/core/Render/GLWidget.h>
#include <livre/core/Render/Viewport.h>
#include <livre/core/Render/View.h>
#include <livre/core/Render/gl.h>

#include <livre/Eq/Render/Shaders/vertRayCast.glsl.h>
#include <livre/Eq/Render/Shaders/fragRayCast.glsl.h>
#include <livre/Eq/Render/RayCastRenderer.h>

#include <eq/eq.h>

uint8_t TF[1024] =
{
0, 125, 255, 0,
0, 123, 255, 0,
0, 120, 255, 0,
0, 118, 255, 0,
0, 116, 255, 0,
0, 114, 255, 1,
0, 112, 255, 1,
0, 109, 255, 1,
0, 107, 255, 1,
0, 105, 255, 2,
0, 103, 255, 2,
0, 101, 255, 2,
0, 98, 255, 2,
0, 96, 255, 3,
0, 94, 255, 3,
0, 92, 255, 3,
0, 90, 255, 3,
0, 87, 255, 4,
0, 85, 255, 4,
0, 83, 255, 4,
0, 81, 255, 4,
0, 79, 255, 4,
0, 76, 255, 5,
0, 74, 255, 5,
0, 72, 255, 5,
0, 70, 255, 5,
0, 68, 255, 6,
0, 65, 255, 6,
0, 63, 255, 6,
0, 61, 255, 6,
0, 59, 255, 7,
0, 57, 255, 7,
0, 54, 255, 7,
0, 52, 255, 7,
0, 50, 255, 8,
0, 48, 255, 8,
0, 46, 255, 8,
0, 43, 255, 8,
0, 41, 255, 8,
0, 39, 255, 9,
0, 37, 255, 9,
0, 35, 255, 9,
0, 32, 255, 9,
0, 30, 255, 10,
0, 28, 255, 10,
0, 26, 255, 10,
0, 24, 255, 10,
0, 21, 255, 11,
0, 19, 255, 11,
0, 17, 255, 11,
0, 15, 255, 11,
0, 13, 255, 12,
0, 10, 255, 12,
0, 8, 255, 12,
0, 6, 255, 12,
0, 4, 255, 12,
0, 2, 255, 13,
0, 0, 255, 13,
2, 0, 255, 13,
4, 0, 255, 13,
6, 0, 255, 14,
8, 0, 255, 14,
10, 0, 255, 14,
13, 0, 255, 14,
15, 0, 255, 15,
17, 0, 255, 15,
19, 0, 255, 15,
21, 0, 255, 15,
24, 0, 255, 16,
26, 0, 255, 16,
28, 0, 255, 16,
30, 0, 255, 16,
32, 0, 255, 16,
35, 0, 255, 17,
37, 0, 255, 17,
39, 0, 255, 17,
41, 0, 255, 17,
43, 0, 255, 18,
46, 0, 255, 18,
48, 0, 255, 18,
50, 0, 255, 18,
52, 0, 255, 19,
54, 0, 255, 19,
57, 0, 255, 19,
59, 0, 255, 19,
61, 0, 255, 20,
63, 0, 255, 20,
65, 0, 255, 20,
68, 0, 255, 20,
70, 0, 255, 20,
72, 0, 255, 21,
74, 0, 255, 21,
76, 0, 255, 21,
79, 0, 255, 21,
81, 0, 255, 22,
83, 0, 255, 22,
85, 0, 255, 22,
87, 0, 255, 22,
90, 0, 255, 23,
92, 0, 255, 23,
94, 0, 255, 23,
96, 0, 255, 23,
98, 0, 255, 24,
101, 0, 255, 24,
103, 0, 255, 24,
105, 0, 255, 24,
107, 0, 255, 24,
109, 0, 255, 25,
112, 0, 255, 25,
114, 0, 255, 25,
116, 0, 255, 25,
118, 0, 255, 26,
120, 0, 255, 26,
123, 0, 255, 26,
125, 0, 255, 26,
127, 0, 255, 27,
136, 0, 255, 27,
145, 0, 255, 27,
154, 0, 255, 27,
163, 0, 255, 28,
172, 0, 255, 28,
181, 0, 255, 28,
190, 0, 255, 28,
200, 0, 255, 29,
209, 0, 255, 29,
218, 0, 255, 29,
227, 0, 255, 29,
236, 0, 255, 29,
245, 0, 255, 30,
254, 0, 255, 30,
255, 0, 246, 30,
255, 0, 237, 30,
255, 0, 228, 31,
255, 0, 219, 31,
255, 0, 210, 31,
255, 0, 201, 31,
255, 0, 192, 32,
255, 0, 183, 32,
255, 0, 174, 32,
255, 0, 164, 32,
255, 0, 155, 33,
255, 0, 146, 33,
255, 0, 137, 33,
255, 0, 128, 33,
255, 0, 119, 34,
255, 0, 116, 34,
255, 0, 112, 34,
255, 0, 109, 34,
255, 0, 105, 35,
255, 0, 102, 35,
255, 0, 98, 35,
255, 0, 95, 35,
255, 0, 91, 36,
255, 0, 88, 36,
255, 0, 84, 36,
255, 0, 81, 36,
255, 0, 77, 37,
255, 0, 74, 37,
255, 0, 70, 37,
255, 0, 67, 37,
255, 0, 63, 38,
255, 0, 60, 38,
255, 0, 56, 38,
255, 0, 53, 39,
255, 0, 49, 39,
255, 0, 46, 39,
255, 0, 42, 39,
255, 0, 39, 40,
255, 0, 35, 40,
255, 0, 32, 40,
255, 0, 28, 41,
255, 0, 25, 41,
255, 0, 22, 41,
255, 0, 18, 42,
255, 0, 15, 42,
255, 0, 11, 42,
255, 0, 8, 42,
255, 0, 4, 43,
255, 0, 1, 43,
255, 2, 0, 43,
255, 5, 0, 44,
255, 9, 0, 44,
255, 12, 0, 45,
255, 16, 0, 45,
255, 19, 0, 45,
255, 23, 0, 46,
255, 26, 0, 46,
255, 30, 0, 46,
255, 33, 0, 47,
255, 37, 0, 47,
255, 40, 0, 48,
255, 44, 0, 48,
255, 47, 0, 49,
255, 51, 0, 49,
255, 54, 0, 50,
255, 58, 0, 50,
255, 61, 0, 51,
255, 65, 0, 51,
255, 68, 0, 52,
255, 72, 0, 52,
255, 75, 0, 53,
255, 79, 0, 53,
255, 82, 0, 54,
255, 86, 0, 55,
255, 89, 0, 55,
255, 93, 0, 56,
255, 96, 0, 57,
255, 100, 0, 57,
255, 103, 0, 58,
255, 106, 0, 59,
255, 110, 0, 60,
255, 113, 0, 61,
255, 117, 0, 62,
255, 120, 0, 62,
255, 124, 0, 63,
255, 127, 0, 64,
255, 131, 0, 66,
255, 134, 0, 67,
255, 138, 0, 68,
255, 141, 0, 69,
255, 145, 0, 70,
255, 148, 0, 72,
255, 152, 0, 73,
255, 155, 0, 75,
255, 159, 0, 76,
255, 162, 0, 78,
255, 166, 0, 79,
255, 169, 0, 81,
255, 173, 0, 83,
255, 176, 0, 85,
255, 180, 0, 87,
255, 183, 0, 89,
255, 187, 0, 92,
255, 190, 0, 94,
255, 194, 0, 97,
255, 197, 0, 99,
255, 201, 0, 102,
255, 204, 0, 105,
255, 208, 0, 108,
255, 211, 0, 112,
255, 215, 0, 115,
255, 218, 0, 119,
255, 222, 0, 123,
255, 225, 0, 127,
255, 229, 0, 131,
255, 232, 0, 136,
255, 235, 0, 140,
255, 239, 0, 145,
255, 242, 0, 150,
255, 246, 0, 156,
255, 249, 0, 162,
255, 253, 0, 168,
253, 255, 0, 175,
249, 255, 0, 182,
246, 255, 0, 189,
242, 255, 0, 197
/*0, 253, 255, 0,
0, 252, 255, 0,
0, 250, 255, 0,
0, 249, 255, 0,
0, 247, 255, 0,
0, 246, 255, 0,
0, 245, 255, 0,
0, 243, 255, 0,
0, 242, 255, 1,
0, 240, 255, 1,
0, 239, 255, 1,
0, 238, 255, 2,
0, 236, 255, 2,
0, 235, 255, 2,
0, 233, 255, 3,
0, 232, 255, 3,
0, 231, 255, 3,
0, 229, 255, 3,
0, 228, 255, 4,
0, 226, 255, 4,
0, 225, 255, 4,
0, 224, 255, 5,
0, 222, 255, 5,
0, 221, 255, 5,
0, 219, 255, 5,
0, 218, 255, 5,
0, 217, 255, 5,
0, 215, 255, 6,
0, 214, 255, 6,
0, 212, 255, 6,
0, 211, 255, 7,
0, 210, 255, 7,
0, 208, 255, 7,
0, 207, 255, 8,
0, 205, 255, 8,
0, 204, 255, 8,
0, 203, 255, 9,
0, 201, 255, 9,
0, 200, 255, 9,
0, 198, 255, 10,
0, 197, 255, 10,
0, 196, 255, 10,
0, 194, 255, 10,
0, 193, 255, 10,
0, 191, 255, 11,
0, 190, 255, 11,
0, 189, 255, 11,
0, 187, 255, 12,
0, 186, 255, 12,
0, 184, 255, 13,
0, 183, 255, 13,
0, 182, 255, 13,
0, 180, 255, 14,
0, 179, 255, 14,
0, 177, 255, 14,
0, 176, 255, 14,
0, 175, 255, 15,
0, 173, 255, 15,
0, 172, 255, 15,
0, 170, 255, 16,
0, 169, 255, 16,
0, 168, 255, 17,
0, 166, 255, 17,
0, 165, 255, 18,
0, 163, 255, 18,
0, 162, 255, 18,
0, 161, 255, 19,
0, 159, 255, 19,
0, 158, 255, 20,
0, 156, 255, 20,
0, 155, 255, 20,
0, 154, 255, 20,
0, 152, 255, 21,
0, 151, 255, 21,
0, 149, 255, 22,
0, 148, 255, 22,
0, 147, 255, 23,
0, 145, 255, 23,
0, 144, 255, 24,
0, 142, 255, 24,
0, 141, 255, 24,
0, 140, 255, 24,
0, 138, 255, 25,
0, 137, 255, 25,
0, 135, 255, 26,
0, 134, 255, 26,
0, 133, 255, 27,
0, 131, 255, 27,
0, 130, 255, 28,
0, 128, 255, 28,
0, 127, 255, 29,
0, 121, 255, 29,
0, 116, 255, 29,
0, 110, 255, 30,
0, 105, 255, 30,
0, 99, 255, 31,
0, 94, 255, 31,
0, 88, 255, 32,
0, 82, 255, 32,
0, 77, 255, 33,
0, 71, 255, 34,
0, 66, 255, 34,
0, 60, 255, 35,
0, 54, 255, 35,
0, 49, 255, 35,
0, 43, 255, 36,
0, 38, 255, 36,
0, 32, 255, 37,
0, 27, 255, 37,
0, 21, 255, 38,
0, 15, 255, 39,
0, 10, 255, 39,
0, 4, 255, 40,
0, 0, 255, 40,
6, 0, 255, 40,
11, 0, 255, 41,
17, 0, 255, 42,
23, 0, 255, 42,
28, 0, 255, 43,
34, 0, 255, 44,
39, 0, 255, 44,
45, 0, 255, 45,
51, 0, 255, 45,
56, 0, 255, 46,
62, 0, 255, 46,
67, 0, 255, 47,
73, 0, 255, 48,
78, 0, 255, 48,
84, 0, 255, 49,
90, 0, 255, 49,
95, 0, 255, 50,
101, 0, 255, 50,
106, 0, 255, 51,
112, 0, 255, 52,
117, 0, 255, 53,
123, 0, 255, 53,
129, 0, 255, 54,
141, 0, 255, 54,
153, 0, 255, 55,
164, 0, 255, 56,
176, 0, 255, 56,
188, 0, 255, 57,
200, 0, 255, 58,
212, 0, 255, 59,
224, 0, 255, 59,
236, 0, 255, 60,
248, 0, 255, 60,
255, 0, 249, 61,
255, 0, 237, 62,
255, 0, 225, 63,
255, 0, 213, 64,
255, 0, 201, 65,
255, 0, 189, 65,
255, 0, 177, 66,
255, 0, 165, 66,
255, 0, 153, 67,
255, 0, 141, 68,
255, 0, 129, 69,
255, 0, 117, 70,
255, 0, 113, 70,
255, 0, 109, 71,
255, 0, 105, 72,
255, 0, 101, 73,
255, 0, 98, 74,
255, 0, 94, 75,
255, 0, 90, 75,
255, 0, 86, 76,
255, 0, 82, 77,
255, 0, 78, 78,
255, 0, 74, 79,
255, 0, 70, 80,
255, 0, 66, 80,
255, 0, 62, 81,
255, 0, 58, 82,
255, 0, 54, 83,
255, 0, 50, 84,
255, 0, 46, 85,
255, 0, 42, 85,
255, 0, 38, 86,
255, 0, 34, 87,
255, 0, 30, 89,
255, 0, 26, 90,
255, 0, 22, 90,
255, 0, 18, 91,
255, 0, 14, 92,
255, 0, 10, 93,
255, 0, 6, 94,
255, 0, 2, 95,
255, 1, 0, 96,
255, 5, 0, 97,
255, 9, 0, 98,
255, 13, 0, 99,
255, 17, 0, 100,
255, 21, 0, 101,
255, 25, 0, 102,
255, 29, 0, 103,
255, 33, 0, 104,
255, 37, 0, 105,
255, 41, 0, 106,
255, 45, 0, 107,
255, 49, 0, 109,
255, 53, 0, 109,
255, 57, 0, 110,
255, 61, 0, 112,
255, 65, 0, 113,
255, 69, 0, 114,
255, 73, 0, 115,
255, 77, 0, 116,
255, 81, 0, 117,
255, 85, 0, 119,
255, 89, 0, 119,
255, 93, 0, 121,
255, 97, 0, 122,
255, 101, 0, 123,
255, 105, 0, 124,
255, 109, 0, 125,
255, 113, 0, 127,
255, 117, 0, 128,
255, 121, 0, 130,
255, 125, 0, 130,
255, 129, 0, 132,
255, 133, 0, 133,
255, 137, 0, 135,
255, 141, 0, 135,
255, 145, 0, 137,
255, 149, 0, 139,
255, 153, 0, 140,
255, 156, 0, 141,
255, 160, 0, 142,
255, 164, 0, 144,
255, 168, 0, 145,
255, 172, 0, 146,
255, 176, 0, 148,
255, 180, 0, 150,
255, 184, 0, 150,
255, 188, 0, 152,
255, 192, 0, 154,
255, 196, 0, 155,
255, 200, 0, 156,
255, 204, 0, 158,
255, 208, 0, 160,
255, 212, 0, 160,
255, 216, 0, 162,
255, 220, 0, 164,
255, 224, 0, 165,
255, 228, 0, 167,
255, 232, 0, 169,
255, 236, 0, 170,
255, 240, 0, 171,
255, 244, 0, 173,
255, 248, 0, 175,
255, 252, 0, 176,
253, 255, 0, 178,
249, 255, 0, 180,
245, 255, 0, 181,
241, 255, 0, 183*/
};

namespace livre
{
namespace
{
std::string where( const char* file, const int line )
{
    return std::string( " in " ) + std::string( file ) + ":" +
           boost::lexical_cast< std::string >( line );
}
}

RayCastRenderer::RayCastRenderer( const GLEWContext* glewContext,
                                  const uint32_t samples,
                                  const uint32_t componentCount,
                                  const GLenum gpuDataType,
                                  const GLint internalFormat )
    : Renderer( componentCount, gpuDataType, internalFormat )
    , nSamples_( samples )
    , transferFunctionTexture_( 0 )
{
    if( !glewContext )
        LBTHROW( std::runtime_error( "No GLEW context given" +
                                     where( __FILE__, __LINE__ )));

    TransferFunction1D< unsigned char > transferFunction;
    initTransferFunction( transferFunction );

    shadersPtr_.reset( new GLSLShaders );

    // TODO: Add the shaders from resource directory
    const int error = shadersPtr_->loadShaders( ShaderData( vertRayCast_glsl,
                                                            fragRayCast_glsl ));
    if( error != GL_NO_ERROR )
        LBTHROW( std::runtime_error( "Can't load glsl shaders: " +
                                     eq::glError( error ) +
                                     where( __FILE__, __LINE__ )));

    framebufferTempTexturePtr_.reset(
        new eq::util::Texture( GL_TEXTURE_RECTANGLE_ARB, glewContext ));
}

RayCastRenderer::~RayCastRenderer()
{
    framebufferTempTexturePtr_->flush();
}

// TODO : a templated initTF function for different kinds of tf ( float, short, etc )
void RayCastRenderer::initTransferFunction( const TransferFunction1D< uint8_t >& /*transferFunction*/ )
{
    //const UInt8Vector& transferFunctionData = transferFunction.getData();

    //assert( transferFunction.getNumChannels() == 4u );

    if( transferFunctionTexture_ == 0 )
    {
        GLuint tfTexture = 0;
        glGenTextures( 1, &tfTexture );
        glBindTexture( GL_TEXTURE_1D, tfTexture );

        glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        std::cout<<"DEBUG COUT:" << TF[ 43 ] << TF[ 135 ] <<std::endl;

        /*glBindTexture( GL_TEXTURE_1D, tfTexture);
        glTexImage1D(  GL_TEXTURE_1D, 0, GL_RGBA, 256u, 0,
                       GL_RGBA, GL_UNSIGNED_BYTE, &TF[0] );*/

        glBindTexture( GL_TEXTURE_1D, tfTexture);
        glTexImage1D(  GL_TEXTURE_1D, 0, GL_RGBA, 256u, 0,
                       GL_RGBA, GL_UNSIGNED_BYTE, &TF[0] );

        transferFunctionTexture_  = tfTexture;
    }
    else
    {
        glBindTexture( GL_TEXTURE_1D, transferFunctionTexture_ );
        glTexImage1D(  GL_TEXTURE_1D, 0, GL_RGBA, 256u, 0,
                       GL_RGBA, GL_UNSIGNED_BYTE, &TF[0] );
    }
}

bool RayCastRenderer::readFromFrameBuffer_( const GLWidget& glWidget,
                                            const View& view,
                                            const Frustum &frustum,
                                            const RenderBrick& renderBrick,
                                            Vector2i& screenPos )
{
    Viewporti pixViewport;
    glWidget.setViewport( &view, pixViewport );

    Vector2i minPos;
    Vector2i maxPos;

    renderBrick.getScreenCoordinates( frustum, pixViewport, minPos, maxPos );

    const Vector2i texSize = maxPos - minPos;

    const eq::fabric::PixelViewport pixelViewPort( minPos[ 0 ], minPos[ 1 ],
                                                   texSize[ 0 ],  texSize[ 1 ] );
    if( !pixelViewPort.hasArea( ) )
        return false;

    framebufferTempTexturePtr_->copyFromFrameBuffer( GL_RGBA, pixelViewPort );

    screenPos = minPos;

    return true;
}

void RayCastRenderer::onFrameStart_( const GLWidget& glWidget LB_UNUSED,
                                     const View& view LB_UNUSED,
                                     const Frustum &frustum,
                                     const RenderBricks& )
{
#ifdef LIVRE_DEBUG_RENDERING
    if( usedTextures_[0] != usedTextures_[1] )
    {
        std::cout << "Render ";
        std::copy( usedTextures_[1].begin(), usedTextures_[1].end(),
                   std::ostream_iterator< uint32_t >( std::cout, " " ));
        std::cout << std::endl;
    }
    usedTextures_[0].swap( usedTextures_[1] );
    usedTextures_[1].clear();
#endif

    glDisable( GL_LIGHTING );
    glDisable( GL_CULL_FACE );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );

    GLSLShaders::Handle shader = shadersPtr_->getProgram( );
    LBASSERT( shader );

    // Enable shaders
    glUseProgramObjectARB( shader );
    GLint tParamNameGL;

    tParamNameGL = glGetUniformLocationARB( shader, "invProjectionMatrix" );
    glUniformMatrix4fv( tParamNameGL, 1, false, frustum.getInvProjectionMatrix( ).array );

    tParamNameGL = glGetUniformLocationARB( shader, "invModelViewMatrix" );
    glUniformMatrix4fv( tParamNameGL, 1, false, frustum.getInvModelViewMatrix( ).array );

    Vector4i viewport;
    glGetIntegerv( GL_VIEWPORT, viewport.array );
    tParamNameGL = glGetUniformLocationARB( shader, "viewport" );
    glUniform4ivARB( tParamNameGL, 1, viewport.array );

    tParamNameGL = glGetUniformLocationARB( shader, "depthRange" );

    Vector2f depthRange;
    glGetFloatv( GL_DEPTH_RANGE, depthRange.array );
    glUniform2fvARB( tParamNameGL, 1, depthRange.array );

    tParamNameGL = glGetUniformLocationARB( shader, "worldEyePosition" );
    glUniform3fvARB( tParamNameGL, 1, frustum.getEyeCoords( ).array );

    // Disable shader
    glUseProgramObjectARB( 0 );
}


void RayCastRenderer::renderBrick_( const GLWidget& glWidget,
                                    const View& view,
                                    const Frustum &frustum,
                                    const RenderBrick& renderBrick )
{
    GLhandleARB shader = shadersPtr_->getProgram( );
    LBASSERT( shader );

    // Enable shaders
    glUseProgramObjectARB( shader );

    if( renderBrick.getTextureState( )->textureId == INVALID_TEXTURE_ID )
    {
        LBERROR << "Invalid texture for node : " << renderBrick.getLODNode( )->getNodeId( ) << std::endl;
        return;
    }

    GLint tParamNameGL = glGetUniformLocationARB( shader, "aabbMin" );
    const ConstLODNodePtr& lodNodePtr = renderBrick.getLODNode( );
    glUniform3fvARB( tParamNameGL, 1, lodNodePtr->getWorldBox( ).getMin( ).array );

    tParamNameGL = glGetUniformLocationARB( shader, "aabbMax" );
    glUniform3fvARB( tParamNameGL, 1, lodNodePtr->getWorldBox( ).getMax( ).array );

    tParamNameGL = glGetUniformLocationARB( shader, "textureMin" );
    ConstTextureStatePtr texState = renderBrick.getTextureState( );
    glUniform3fvARB( tParamNameGL, 1, texState->textureCoordsMin.array );

    tParamNameGL = glGetUniformLocationARB( shader, "textureMax" );
    glUniform3fvARB( tParamNameGL, 1, texState->textureCoordsMax.array );

    const Vector3f voxSize = renderBrick.getTextureState( )->textureSize / lodNodePtr->getWorldBox( ).getDimension( );
    tParamNameGL = glGetUniformLocationARB( shader, "voxelSpacePerWorldSpace" );
    glUniform3fvARB( tParamNameGL, 1, voxSize.array );

    // Read from buffer and getthe position screen
    Vector2i screenPos;
    if( !readFromFrameBuffer_( glWidget, view, frustum, renderBrick, screenPos ))
    {
        glUseProgramObjectARB( 0 );
        return;
    }

    // Put data to the shader
    tParamNameGL = glGetUniformLocationARB( shader, "screenPos" );
    glUniform2ivARB( tParamNameGL, 1, screenPos.array );

    glActiveTextureARB( GL_TEXTURE2 );
    framebufferTempTexturePtr_->bind( );
    framebufferTempTexturePtr_->applyZoomFilter( eq::FILTER_LINEAR );
    framebufferTempTexturePtr_->applyWrap( );

    tParamNameGL = glGetUniformLocationARB( shader, "frameBufferTex" );
    glUniform1iARB( tParamNameGL, 2 );

    glActiveTextureARB( GL_TEXTURE1 );
    glBindTexture( GL_TEXTURE_1D, transferFunctionTexture_ ); //preintegrated values
    tParamNameGL = glGetUniformLocationARB( shader, "transferFnTex" );
    glUniform1iARB( tParamNameGL, 1 ); //f-shader

    glActiveTextureARB( GL_TEXTURE0 );
    texState->bind( );
    tParamNameGL = glGetUniformLocationARB( shader, "volumeTex" );
    glUniform1iARB( tParamNameGL, 0 ); //f-shader

    tParamNameGL = glGetUniformLocationARB(  shader, "nSamples" );
    glUniform1iARB( tParamNameGL, nSamples_ );

    const uint32_t refLevel = renderBrick.getLODNode( )->getRefLevel( );

    tParamNameGL = glGetUniformLocationARB(  shader, "refLevel" );
    glUniform1iARB( tParamNameGL, refLevel );

#ifdef LIVRE_DEBUG_RENDERING
    usedTextures_[1].push_back( texState->textureId );
#endif
    renderBrick.drawBrick( true /* draw front */, false /* cull back */ );

    glUseProgramObjectARB( 0 );
}

}

