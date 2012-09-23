#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

#include <boost/filesystem.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace boost;

int main(int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);

    //Read in our files and sort them into the correct order
    boost::filesystem::path pcd_dir("/home/andrew/School/Kinect/data/room_1");
    vector<boost::filesystem::path> pcd_files;
    vector<boost::filesystem::path>::iterator pcd_itr;
    copy(boost::filesystem::directory_iterator(pcd_dir),
            boost::filesystem::directory_iterator(), back_inserter(pcd_files));
    sort(pcd_files.begin(), pcd_files.end());

    //Load our files one by one and display their clouds
    BOOST_FOREACH(boost::filesystem::path pcd_file, pcd_files)
    {
        if(pcl::io::loadPCDFile<pcl::PointXYZRGBA>(pcd_file.string(), *cloud) == -1)  
        {
            PCL_ERROR("Couldn't read file!");
            return(-1);
        }

        std::cout << "Loaded" << cloud->width * cloud->height << "data points " << std::endl;
    }
    
    return(0);
}
