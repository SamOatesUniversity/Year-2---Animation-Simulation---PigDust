#include "ASPX.h"
 
namespace ASPX
{
    float random( float min, float max )
    {
        float randPerent = (float)rand() / ( RAND_MAX + 1.0f );
        float range = ( max - min ) + 1.0f;
        return min + ( range * randPerent );
    }
 
    namespace Kinematics
    {
        void Euler( twm::Vector &value, const twm::Vector &derivative, float h )
        {
            value += derivative * h;
        }
    }
 
    namespace Transformation
    {
        twm::Matrix Position( float x, float y, float z )
        {
            return twm::Matrix( 1,  0,  0,  0,
                                0,  1,  0,  0,
                                0,  0,  1,  0,
                                x,  y,  z,  1 );
        }
 
        twm::Matrix Position( twm::Vector xyz )
        {
            return twm::Matrix( 1,      0,      0,      0,
                                0,      1,      0,      0,
                                0,      0,      1,      0,
                                xyz.x,  xyz.y,  xyz.z,  1 );
        }
 
        twm::Matrix Rotate( float x, float y, float z )
        {
            x = Conversion::DegreesToRad( x );
            y = Conversion::DegreesToRad( y );
            z = Conversion::DegreesToRad( z );
 
            twm::Matrix xMatrix(    1,              0,              0,              0,
                                    0,              cos(x),         -sin(x),        0,
                                    0,              sin(x),         cos(x),         0,
                                    0,              0,              0,              1);
 
            twm::Matrix yMatrix(    cos(y),         0,              sin(y),         0,
                                    0,              1,              0,              0,
                                    -sin(y),        0,              cos(y),         0,
                                    0,              0,              0,              1);
 
            twm::Matrix zMatrix(    cos(z),         -sin(z),        0,              0,
                                    sin(z),         cos(z),         0,              0,
                                    0,              0,              1,              0,
                                    0,              0,              0,              1);
 
            return xMatrix * yMatrix * zMatrix;
        }
 
        twm::Matrix Rotate( twm::Vector xyz )
        {
            float x = Conversion::DegreesToRad( xyz.x );
            float y = Conversion::DegreesToRad( xyz.y );
            float z = Conversion::DegreesToRad( xyz.z );
 
            twm::Matrix xMatrix(    1,              0,              0,              0,
                                    0,              cos(x),         -sin(x),        0,
                                    0,              sin(x),         cos(x),         0,
                                    0,              0,              0,              1);
 
            twm::Matrix yMatrix(    cos(y),         0,              sin(y),         0,
                                    0,              1,              0,              0,
                                    -sin(y),        0,              cos(y),         0,
                                    0,              0,              0,              1);
 
            twm::Matrix zMatrix(    cos(z),         -sin(z),        0,              0,
                                    sin(z),         cos(z),         0,              0,
                                    0,              0,              1,              0,
                                    0,              0,              0,              1);
 
            return xMatrix * yMatrix * zMatrix;
        }
 
        twm::Vector getPosition( twm::Matrix xform )
        {
            return twm::Vector( xform.m30, xform.m31, xform.m32 );
        }
 
        twm::Vector getDirection( twm::Matrix xform )
        {
            return twm::Vector( xform.m20, xform.m21, xform.m22 );
        }
    }
 
    namespace Conversion
    {
        float DegreesToRad( float deg )
        {
            return deg * 0.017453f;
        }
 
        float RadToDegrees( float rad )
        {
            return rad * 57.29578f;
        }
 
        twm::Vector HVecToVec( twm::HVector hvec )
        {
            return twm::Vector( hvec.x, hvec.y, hvec.z );
        }
 
        twm::Vector LocalToWorld( twm::Vector vec, twm::Matrix World )
        {
            return HVecToVec( twm::HVector( vec, 0.0f ) * World );
        }
    }
 
    namespace Interpolation
    {
        float Smoothstep( float min, float max, float x )
        {
            return ( (x) * (x) * ( 3 - 2 * x ) );
        }
 
        float Percentage ( float min, float max, float x )
        {
            return ( x - min ) / ( max - min );
        }
    }
 
    namespace KeyFrame
    {
        CKeyFrame::CKeyFrame(void)
        {
            activeFrame_ = 0;
            animationLength_ = 0.0f;
        }
 
        CKeyFrame::~CKeyFrame(void)
        {
        }
 
        void CKeyFrame::addFrame( twm::Vector value, float time )
        {
            SKeyFrame frame;
            frame.value = value;
            frame.time = time;
            frame_.push_back( frame );
 
            animationLength_ = time;
            intialTime_ = frame_[0].time;
        }
 
        void CKeyFrame::update( twm::Vector &vector, float time )
        {
            //Calculate the percentage with respect to time
            float s = Interpolation::Percentage( frame_[activeFrame_].time, frame_[activeFrame_+1].time, time );
 
            //Work out the new position
            float smooth = Interpolation::Smoothstep( frame_[activeFrame_].time, frame_[activeFrame_+1].time, Interpolation::Clamp( 0.0f, 1.0f, s ) );
            vector = Interpolation::Lerp( frame_[activeFrame_].value, frame_[activeFrame_+1].value, smooth );
 
            //If current time is the next frames start time, increase the current frame
            if( time >= frame_[activeFrame_+1].time - 0.05f ) activeFrame_++;
 
            //If the active frame is greater than the frame count
            //Increase each frames time by the complete animation length
            //and set the active frame back to zero
            if( activeFrame_ >= frame_.size() )
            {
                for( unsigned int i = 0; i < frame_.size(); i++ )
                    frame_[i].time += (animationLength_ - intialTime_);
 
                activeFrame_ = 0;
            }
        }
 
        void CKeyFrame::clear( void )
        {
            frame_.clear();
            activeFrame_ = 0;
            animationLength_ = 0.0f;
        }
 
        SKeyFrame CKeyFrame::getFrameValue( int id )
        {
            if( id < 0 || (unsigned)id > ( frame_.size() - 1 ) ) id = 0;
            return frame_[id];
        }
    }
 
    namespace Path
    {
        twm::Matrix Frenet( const twm::Vector& pos, const twm::Vector& dir, const twm::Vector& up )
        {
            const twm::Vector W = twm::Unit( dir );
            const twm::Vector U = twm::Unit( twm::Cross( up, W ) );
            const twm::Vector V = twm::Cross( W, U );
 
            return twm::Matrix( U.x,    U.y,    U.z,    0,
                                V.x,    V.y,    V.z,    0,
                                W.x,    W.y,    W.z,    0,
                                pos.x,  pos.y,  pos.z,  1 );
        }
 
        twm::Vector Bezier( twm::Vector& p0, twm::Vector& p1, float time )
        {
            return p0 + ( time * ( p0 - p1 ) );
        }
 
        twm::Vector Bezier( twm::Vector& p0, twm::Vector& p1, twm::Vector& p2, twm::Vector& p3, float time )
        {
            return pow( 1.0f - time, 3.0f ) * p0
                   + ( 3 * pow( 1.0f - time, 2.0f ) * ( time * p1 ) )
                   + ( 3 * ( 1.0f - time ) * ( pow( time, 2.0f ) * p2 ) )
                   + ( pow( time, 3.0f ) * p3 );
        }
 
        twm::Vector BezierTangent( twm::Vector& p0, twm::Vector& p1, float time )
        {
            return ( p1 + p0 );
        }
 
        twm::Vector BezierTangent( twm::Vector& p0, twm::Vector& p1, twm::Vector& p2, twm::Vector& p3, float time )
        {
            return ( -3 * pow( 1.0f - time, 2.0f ) * p0 )
                    + ( ( 3 - (12 * time) + ( 9 * ( time * time ) ) ) * p1 )
                    + ( ( 3 * ( time * time ) ) * p3 );
        }
    }
}