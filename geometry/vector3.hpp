#pragma once

#include <cmath>

namespace vector
{    
    struct vector3 {
        int x;
        int y;
        int z;

        vector3(int x, int y, int z);
        vector3();
    };



    vector3::vector3(int x, int y, int z) : x(x), y(y), z(z) { }

    /**
     * @brief 
     * 
     * @param factor the scaling factor
     */
    vector3 scale(const vector3 vector, const int factor) {
        return vector3(vector.x * factor, vector.y * factor, vector.z * factor);
    }
    vector3 scale(const vector3 vector, const vector3 factors) {
        return vector3(vector.x * factors.x, vector.y * factors.y, vector.z * factors.z);
    }

    /**
     * @brief 
     * 
     * @param addend the vector to add
     */
    vector3 add(const vector3 vec1, const vector3 vec2) {
        return vector3(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
    }


    /**
     * @brief returns the length of this vector
     * 
     * @return float the length calculated by pythagoreans theorem
     */
    float length(const vector3 vector) {
        return sqrt(pow(vector.x,2) + pow(vector.y, 2) + pow(vector.z,2));
    }

    /**
     * @brief checks whether this vector2 lies within the rectangle defined by the given vectors (both included)
     * 
     * @param topLeft 
     * @param bottomRight 
     * @return true 
     * @return false 
     */
    bool isWithin(const vector3 target, const vector3 from, const vector3 to) {
        return (target.x >= from.x && target.x <= to.x 
            && target.y >= from.y && target.y <= to.y 
            && target.z >= from.z && target.z <= to.z );
    }

    /**
     * @brief calculates the volume of a cube spanning from (0,0,0) to this vectors value by multiplying the x, y and z coordinate
     * 
     * @return int 
     */
    int volume(const vector3 vec) {
        return vec.x * vec.y * vec.z;
    }

    int scalar(const vector3 vec1, const vector3 vec2) {
        return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z; 
    }



    /**
     * @brief overloaded + operator that adds to vectors together
     * 
     * @param addend 
     * @return vector3 
     */
    vector3 operator+(vector3 vec, vector3 addend) {
        return add(vec, addend);
    }

    /**
     * @brief overloaded * operator, that mutliplies a vector by a given integer
     * 
     * @param addend 
     * @return vector23 
     */
    vector3 operator*(vector3 vec, int factor){
        return scale(vec, factor);
    }
    vector3 operator*(vector3 vec, vector3 factors){
        return scale(vec, factors);
    }
}



typedef vector::vector3 vector3;
typedef vector::vector3 vec3;

#define v(x,y,z) (vector3(x,y,z))