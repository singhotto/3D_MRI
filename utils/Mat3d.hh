#ifndef MAT_3D__GUARD
#define MAT_3D__GUARD

#include<cassert>
#include<iostream>

class Mat3d
{
private:
    float* data;
    int n_rows;
    int n_cols;
    int n_imgs;
public:
    Mat3d(int r, int c, int i);
    Mat3d(const Mat3d& other);
    Mat3d(Mat3d&& other) noexcept;
    Mat3d& operator=(const Mat3d& other);
    Mat3d& operator=(Mat3d&& other) noexcept;
    ~Mat3d();

    float operator()(int r, int c, int i);
    float at(int r, int c, int i);
    float at(int i);
    void setData(int i, float x);

    int getRows() const;
    int getCols() const;
    int getImgSize() const;
};


#endif