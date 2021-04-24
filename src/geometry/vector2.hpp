#pragma once

#include <cmath>

namespace vector
{   
    struct vector2 {
        int x;
        int y;

        vector2(int x, int y);
        vector2();

        void add(vector2 addend);
        void scale(int factor);
        float length();

        int area();

        bool isWithin(vector2 topLeft, vector2 bottomRight);

        vector2 operator*(const int& scale);
        vector2 operator+(const vector2& addend);
    };

    vector2::vector2(int x, int y) : x(x), y(y){ }

    /**
     * @brief scales this vector2 by a given factor by multiplying all coordinates with it.
     * 
     * @param factor the scaling factor
     */
    void  vector2::scale(int factor){
        x *= factor;
        y *= factor;
    }

    /**
     * @brief adds a given vector2 to this one, by adding the individual coordinates.
     * 
     * @param addend the vector to add
     */
    void  vector2::add(vector2 addend){
        x += addend.x;
        y += addend.y;
    }

    /**
     * @brief returns the length of this vector
     * 
     * @return float the length calculated by pythagoreans theorem
     */
    float  vector2::length(){
        return sqrt(pow(x,2) + pow(y,2));
    }

    /**
     * @brief checks whether this vector2 lies within the rectangle defined by the given vectors (both included)
     * 
     * @param topLeft 
     * @param bottomRight 
     * @return true 
     * @return false 
     */
    bool  vector2::isWithin(vector2 topLeft, vector2 bottomRight){
        if( x >= topLeft.x && x <= bottomRight.x || y >= bottomRight.y || y <= topLeft.y ){
            return false;
        } else{ 
            return true;
        }
    }

    /**
     * @brief calculates the area of a rectangle spanning from (0,0) to this vectors value by multiplying the x and y coordinate
     * 
     * @return int 
     */
    int  vector2::area(){
        return x * y;
    }


    /**
     * @brief overloaded + operator, that adds to vectors together
     * 
     * @param addend 
     * @return vector2 
     */
    vector2  vector2::operator+(const vector2& addend){
        vector2 result = vector2(x,y);
        result.add(addend);
        return result;
    }

    /**
     * @brief overloaded * operator, that mutliplies a vector by a given integer
     * 
     * @param addend 
     * @return vector2 
     */
    vector2  vector2::operator*(const int& scale){
        vector2 result = vector2(x,y);
        result.scale(scale);
        return result;
    }


    std::string to_string(vector2 vec) {
        return "(" + std::to_string(vec.x) + "," + std::to_string(vec.y) + ")";
    }

};

typedef vector::vector2 vector2;
typedef vector::vector2 vec2;

#define v(x,y) (vector2(x,y))