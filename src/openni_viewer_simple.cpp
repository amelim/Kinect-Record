#include <pcl/io/openni_grabber.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <string>

int im_count = 0;
std::string prefix = "kinect_";
std::string postfix = ".pcd";

class SimpleOpenNIViewer
{
    public:
        SimpleOpenNIViewer () : viewer("PCL OpenNI Viewer") {}

        void cloud_cb_(const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr& cloud)
        {
            if(!viewer.wasStopped()) 
            {
                std::cin.get();
                viewer.showCloud(cloud);
                std::string filename = prefix + boost::lexical_cast<std::string>(im_count) + postfix;
                im_count++;
                pcl::io::savePCDFileASCII(filename, *cloud);
            }
        }

        void run()
        {
            pcl::Grabber* interface = new pcl::OpenNIGrabber(); 

            boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f = 
                boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

            interface->registerCallback(f);
            interface->start();

            while(!viewer.wasStopped())
                boost::this_thread::sleep (boost::posix_time::seconds(1));

            interface->stop();
        }

        pcl::visualization::CloudViewer viewer;
};

int main()
{
    SimpleOpenNIViewer v;
    v.run();
    return 0;
}
