#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualizaiton/cloud_viewer.h>

#include <boost/filesystem.hpp>

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

    //Read in our files and sort them into the correct order
    path pcd_dir("/home/andrew/School/Kinect/data/desk_1");
    vector<path> pcd_files;
    vector<path>::iterator pcd_itr;
    copy(directory_iterator(pcd_dir), directory_iterator(), back_inserter(pcd_files));
    sort(pcd_files.begin(), pcd_files.end());

    //Load our files one by one and display their clouds
    BOOST_FOREACH(path pcd_file, pcd_files)
    {
        if(pcl::io::loadPCDFile<pcl::PointXYZ>("somefile", *cloud) == -1)  
        {
            PCL_ERROR("Couldn't read file!");
            return(-1);
        }
    }
    
    return(0);
}
