#pragma once

#include <vector>
#include <iostream>
#include "ASPP.h"

#include "twm/util/math.hpp"
using namespace twm::operators;

namespace ASPX
{
    float random( float min = 0.0f, float max = 1.0f );
     
    namespace Kinematics
    {
        void Euler( twm::Vector &value, const twm::Vector &derivative, float h );
    }
 
    namespace Transformation
    {
        twm::Matrix Position( float x, float y, float z );
        twm::Matrix Position( twm::Vector xyz );
        twm::Matrix Rotate( float x, float y, float z );
        twm::Matrix Rotate( twm::Vector xyz );
 
        twm::Vector getPosition( twm::Matrix xform );
        twm::Vector getDirection( twm::Matrix xform );
    }
 
    namespace Conversion
    {
        float DegreesToRad( float deg );
        float RadToDegrees( float rad );
        twm::Vector HVecToVec( twm::HVector hvec );
        twm::Vector LocalToWorld( twm::Vector vec, twm::Matrix World );
    }
 
    namespace Interpolation
    {
        template <class T>
        T Lerp( T p0, T p1, float s )
        {
            return p0 + (p1 - p0 ) * s;
        }
 
        template <class T>
        T Clamp( T min, T max, T x )
        {
            if( x < min ) return min;
            if( x > max ) return min;
            return x;
        }
 
        template <class T>
        T LerpBetween( T current, T destination, float start_time, float length, float time )
        {
            float s = ASPX::Interpolation::Percentage(  start_time,
                                                        start_time + length,
                                                        time );
 
            float smooth = ASPX::Interpolation::Smoothstep( start_time,
                                                            start_time + length,
                                                            ASPX::Interpolation::Clamp( 0.0f, 1.0f, s ) );
 
            return ASPX::Interpolation::Lerp( current, destination, smooth );
        }
 
        float Percentage( float min, float max, float x );
        float Smoothstep( float min, float max, float x );
    }
 
    namespace KeyFrame
    {
        struct SKeyFrame {
            twm::Vector value;
            float time;
        };
 
        class CKeyFrame
        {
        private:
            std::vector< SKeyFrame > frame_;
            unsigned int activeFrame_;
            float animationLength_, intialTime_;
        public:
            CKeyFrame(void);
            ~CKeyFrame(void);
 
            void addFrame( twm::Vector value, float time );
            void update( twm::Vector &vector, float time );
            void clear( void );
 
            SKeyFrame getFrameValue( int id );
            unsigned int lastFrame( void ) { return frame_.size() - 1; }
            unsigned int activeFrame( void ) { return activeFrame_; }
        };
    }
 
    namespace Path
    {
        twm::Matrix Frenet( const twm::Vector& pos, const twm::Vector& dir, const twm::Vector& up );
 
        twm::Vector Bezier( twm::Vector& p0, twm::Vector& p1, float time );
        twm::Vector Bezier( twm::Vector& p0, twm::Vector& p1, twm::Vector& p2, float time );
        twm::Vector Bezier( twm::Vector& p0, twm::Vector& p1, twm::Vector& p2, twm::Vector& p3, float time );
 
        twm::Vector BezierTangent( twm::Vector& p0, twm::Vector& p1, float time );
        twm::Vector BezierTangent( twm::Vector& p0, twm::Vector& p1, twm::Vector& p2, float time );
        twm::Vector BezierTangent( twm::Vector& p0, twm::Vector& p1, twm::Vector& p2, twm::Vector& p3, float time );
    }
}