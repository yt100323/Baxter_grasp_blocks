// pcl_grabing.h header file
// Zhiang Chen, Nov 2015
// for pcl in final project 

#ifndef PCL_GRABING_H_
#define PCL_GRABING_H_

#include <cwru_pcl_utils/cwru_pcl_utils.h>
#include <geometry_msgs/Pose.h>
#include <Eigen/Eigen> 
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>
#include <string>

#define REAL_WORLD



#ifdef GAZEBO
#define roughHeight -0.15
#define HeightRange 0.05
#define roughColor_R 74
#define roughColor_G 138
#define roughColor_B 169
#define ColorRange 10
#define Table_X_Min -10
#define Table_X_Max 10
#define Table_Y_Min -10
#define Table_Y_Max 10
#define Eps 0.15 
#define TableRadius 0.4
#define HandMinHeight 0.1
#define BlockMaxHeight 0.1
#define BlockTopRadius 0.006
#define BlockRadius 0.05
#endif

#ifdef REAL_WORLD
#define roughHeight -0.136//-0.129	//table Height  -0.223366
#define HeightRange 0.03	//table searching z range
#define roughColor_R 140	//table color
#define roughColor_G 120
#define roughColor_B 120
#define ColorRange 60		//table color tor
#define Table_X_Min 0.3		//table searching x and y range
#define Table_X_Max 1.2
#define Table_Y_Min -0.5
#define Table_Y_Max 0.5
#define Eps 0.15 			//
#define TableRadius 0.35	//table r
#define HandMinHeight 0.1	//
#define BlockMaxHeight 0.1
#define BlockTopRadius 0.007
#define BlockRadius 0.05
#endif

class Pcl_grabing
{
public:
    Pcl_grabing(ros::NodeHandle* nodehandle);  // constructor
    bool findTableTop(); //
    bool checkForHand();
    bool isBlock(); //
    geometry_msgs::Pose getBlockPose(); //
    void getBlockVector(Vector3f &plane_normal, Vector3f &major_axis, Vector3f &centroid);
    Eigen::Vector3d getColor();
    std::string getColor2();

    CwruPclUtils pcl_wsn;
    //float getWidth();
    //float getHeight();
private:
    void update_kinect_points();
    void transform_clr_kinect_cloud(Eigen::Affine3f A);
    geometry_msgs::Pose transformEigenAffine3dToPose(Eigen::Affine3d e);
    void display_points(PointCloud<pcl::PointXYZ> points);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr pclKinect_clr_ptr_;   
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr transformed_pclKinect_clr_ptr_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr display_ptr_;
    ros::Publisher points_publisher;  
    geometry_msgs::Pose BlockPose;
    Eigen::Vector3d BlockColor;
    double TableHeight;
    Eigen::Vector3d TableColor;
    Eigen::Vector3f TableCentroid;
    
    Eigen::Vector3f Block_Major;
    Eigen::Vector3f Block_Normal;
    Eigen::Vector3f BlockTopCentroid;


    ros::Subscriber pointcloud_subscriber_;
    bool got_kinect_cloud_;
    void KinectCameraCB(const sensor_msgs::PointCloud2ConstPtr& cloud) ;
    bool got_kinect_cloud() { return got_kinect_cloud_; };
    void reset_got_kinect_cloud() {got_kinect_cloud_= false;};
    void set_got_kinect_cloud() {got_kinect_cloud_ = true;};
};

#endif // PCL_GRABING_H_
