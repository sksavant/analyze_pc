#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>

#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/keypoints/harris_keypoint3D.h>

class AnalyzePC {
  public:
    AnalyzePC();
    void spin();

  private:
    ros::NodeHandle nh;
    ros::Publisher vis_pub;
    ros::Publisher kpg_pub;
    ros::Publisher kpq_pub;
    ros::Subscriber gt_cloud_sub;
    ros::Subscriber qd_cloud_sub;
    ros::ServiceServer set_parameters_server;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr gt_cloud;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr qd_cloud;
    std::vector<float> error_data;

    pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;

    void gtCloudCb(const sensor_msgs::PointCloud2ConstPtr& input);
    void qdCloudCb(const sensor_msgs::PointCloud2ConstPtr& input);
    bool setParamCb(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);
    void visualizeError();
    void showKeyPoints();

    double harris_radius;
};
