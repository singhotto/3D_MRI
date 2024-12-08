#include "Mat3d.hh"

Mat3d::Mat3d(int r, int c, int i) : n_rows(r), n_cols(c), n_imgs(i)
{
    data = new float[r*c*i];
    std::memset(data, 0, sizeof(float) * n_rows * n_cols * n_imgs);
}

Mat3d::Mat3d(const Mat3d& other)
    : n_rows(other.n_rows), n_cols(other.n_cols), n_imgs(other.n_imgs)
{
    data = new float[n_rows * n_cols * n_imgs];
    std::memcpy(data, other.data, sizeof(float) * n_rows * n_cols * n_imgs);  
}

Mat3d::Mat3d(Mat3d&& other) noexcept
    : data(other.data), n_rows(other.n_rows), n_cols(other.n_cols), n_imgs(other.n_imgs)
{
    other.data = nullptr; 
    other.n_rows = 0;
    other.n_cols = 0;
    other.n_imgs = 0;
}

Mat3d& Mat3d::operator=(const Mat3d& other)
{
    if (this != &other) {  
        delete[] data;  

        n_rows = other.n_rows;
        n_cols = other.n_cols;
        n_imgs = other.n_imgs;
        data = new float[n_rows * n_cols * n_imgs];
        std::memcpy(data, other.data, sizeof(float) * n_rows * n_cols * n_imgs);
    }
    return *this;
}

Mat3d& Mat3d::operator=(Mat3d&& other) noexcept
{
    if (this != &other) {
        delete[] data;  

        data = other.data;
        n_rows = other.n_rows;
        n_cols = other.n_cols;
        n_imgs = other.n_imgs;

        other.data = nullptr;
        other.n_rows = 0;
        other.n_cols = 0;
        other.n_imgs = 0;
    }
    return *this;
}

Mat3d::~Mat3d()
{
    if(data)
        delete[] data;
}

float Mat3d::operator()(int r, int c, int i)
{
    return at(r, c, i);
}

float Mat3d::at(int r, int c, int i)
{
    assert(r>= 0 && r<n_rows);
    assert(c>= 0 && c<n_cols);
    assert(i>= 0 && i<n_imgs);

    int index = r * n_cols * n_imgs + c * n_imgs + i;
    return data[index];
}

float Mat3d::at(int i)
{
    assert(i>=0&& i<(n_rows*n_cols*n_cols));
    return data[i];
}

void Mat3d::setData(int i, float x)
{
    assert(i>=0&& i<(n_rows*n_cols*n_cols));
    data[i] = x;
}

int Mat3d::getRows() const
{
    return n_rows;
}

int Mat3d::getCols() const
{
    return n_cols;
}

int Mat3d::getImgSize() const
{
    return n_imgs;
}
