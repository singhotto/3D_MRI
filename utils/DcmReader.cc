#include "DcmReader.hh"
#include <stdexcept>

DcmReader::DcmReader() {
    // Initialize any necessary data members here if needed
}

DcmReader &DcmReader::getInstance()
{
    static DcmReader instance; // Guaranteed to be destroyed, instantiated on first use.
    return instance;
}

Mat3d DcmReader::getMat(const std::string path)
{
    // Read the DICOM file
    gdcm::ImageReader reader;
    reader.SetFileName(path.c_str());
    if (!reader.Read()) {
        throw std::runtime_error("Failed to read DICOM file!");
    }

    // Access the image data
    const gdcm::Image &image = reader.GetImage();

    // Get the image dimensions (no need to pass an array)
    const unsigned int* dimensions = image.GetDimensions();

    if (!dimensions || dimensions[0] == 0 || dimensions[1] == 0 || dimensions[2] == 0) {
        throw std::runtime_error("Invalid DICOM dimensions.");
    }
    //Create Matrix 
    Mat3d mat(dimensions[0], dimensions[1], dimensions[2]);

    // std::cout << "Dimensions: " << dimensions[0] << "x" << dimensions[1] << "x" << dimensions[2] << std::endl;

    // Access pixel data
    size_t bufferLength = image.GetBufferLength();
    // std::cout<<"Buffer length: "<<bufferLength<<std::endl;
    // std::cout<<"HxL: "<<dimensions[0] * dimensions[1] * dimensions[2]<<std::endl;
    char *buffer = new char[bufferLength];
    image.GetBuffer(buffer);

    // Process the data (example: print the first few bytes)
    for (size_t i = 0; i < bufferLength; ++i) {
        unsigned int px = (unsigned int)(unsigned char)buffer[i];
        mat.setData(i, (float)px/255.0f);
    }
    delete[] buffer;
    return mat;
}
