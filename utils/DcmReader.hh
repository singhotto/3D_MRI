#ifndef DCM_READER__HH
#define DCM_READER__HH

#include <string>
#include "Mat3d.hh"
#include <gdcmImageReader.h>
#include <gdcmImage.h>
#include <gdcmDataSet.h>

class DcmReader
{
private:
    // Private constructor to prevent instantiation
    DcmReader();

    // Delete copy constructor and assignment operator to avoid copies
    DcmReader(const DcmReader&) = delete;
    DcmReader& operator=(const DcmReader&) = delete;

public:
    static DcmReader& getInstance();

    Mat3d getMat(const std::string path);
};

#endif