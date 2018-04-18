/**
* @file single_board.cpp
* @author Hamdi Sahloul
* @date September 2014
* @version 0.1
* @brief ROS version of the example named "simple_board" in the Aruco software package.
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <map>


#include <aruco.h>
//#include <aruco/boarddetector.h>
//#include <aruco/cvdrawingutils.h>
#include <ar_sys/utils.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

using namespace aruco;

class ArSysSingleBoard
{
	private:
    cv::Mat InImage, resultImg;
		aruco::CameraParameters camParam;
		bool useRectifiedImages;
		bool draw_markers;
		bool draw_markers_cube;
		bool draw_markers_axis;
    bool publish_tf;
    MarkerDetector MDetector;
    vector< Marker >  Markers;

    // ARUCO 2.0 Marker Map Replaces board
    MarkerMap the_marker_map_config;

    ros::Subscriber cam_info_sub;
		bool cam_info_received;
		image_transport::Publisher image_pub;
		image_transport::Publisher debug_pub;
		ros::Publisher pose_pub;
		ros::Publisher transform_pub; 
		ros::Publisher position_pub;
    std::string marker_set_frame;

		double marker_size;
    std::string marker_set_config;

		ros::NodeHandle nh;
		image_transport::ImageTransport it;
		image_transport::Subscriber image_sub;

		tf::TransformListener _tfListener;

	public:
		ArSysSingleBoard()
			: cam_info_received(false),
			nh("~"),
			it(nh)
		{
			image_sub = it.subscribe("/image", 1, &ArSysSingleBoard::image_callback, this);
			cam_info_sub = nh.subscribe("/camera_info", 1, &ArSysSingleBoard::cam_info_callback, this);

			image_pub = it.advertise("result", 1);
			debug_pub = it.advertise("debug", 1);
			pose_pub = nh.advertise<geometry_msgs::PoseStamped>("pose", 100);
			transform_pub = nh.advertise<geometry_msgs::TransformStamped>("transform", 100);
			position_pub = nh.advertise<geometry_msgs::Vector3Stamped>("position", 100);

			nh.param<double>("marker_size", marker_size, 0.05);
      nh.param<std::string>("marker_set_config", marker_set_config, "markerSetConfig.yml");
      nh.param<std::string>("marker_set_frame", marker_set_frame, "");
			nh.param<bool>("image_is_rectified", useRectifiedImages, true);
			nh.param<bool>("draw_markers", draw_markers, false);
			nh.param<bool>("draw_markers_cube", draw_markers_cube, false);
			nh.param<bool>("draw_markers_axis", draw_markers_axis, false);
      nh.param<bool>("publish_tf", publish_tf, false);

      the_marker_map_config.readFromFile(marker_set_config.c_str());

      if ( the_marker_map_config.isExpressedInPixels() && marker_size>0)
                  the_marker_map_config=the_marker_map_config.convertToMeters(marker_size);

			ROS_INFO("ArSys node started with marker size of %f m and board configuration: %s",
           marker_size, marker_set_config.c_str());
		}

		void image_callback(const sensor_msgs::ImageConstPtr& msg)
		{
      static tf::TransformBroadcaster br;
            
			if(!cam_info_received) return;

			cv_bridge::CvImagePtr cv_ptr;
			try
			{
				cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
        InImage = cv_ptr->image;
				resultImg = cv_ptr->image.clone();

        //set the appropiate dictionary type so that the detector knows it
        MDetector.setDictionary(the_marker_map_config.getDictionary());
        // detect markers without computing R and T information
        Markers=MDetector.detect(InImage);


        //detect the 3d camera location wrt the markerset (if possible)
        if ( the_marker_map_config.isExpressedInMeters() && camParam.isValid()) {
          MarkerMapPoseTracker MSPoseTracker;//tracks the pose of the marker map
          MSPoseTracker.setParams(camParam,the_marker_map_config);
          if ( MSPoseTracker.estimatePose(Markers)){//if pose correctly computed, print the reference system
            aruco::CvDrawingUtils::draw3dAxis(InImage,camParam,MSPoseTracker.getRvec(),MSPoseTracker.getTvec(),the_marker_map_config[0].getMarkerSize()*2);
            tf::Transform transform = ar_sys::getTf(MSPoseTracker.getRvec(), MSPoseTracker.getTvec());
            tf::StampedTransform stampedTransform(transform, msg->header.stamp, msg->header.frame_id, marker_set_frame);
            if (publish_tf)
              br.sendTransform(stampedTransform);
            geometry_msgs::PoseStamped poseMsg;
            tf::poseTFToMsg(transform, poseMsg.pose);
            poseMsg.header.frame_id = msg->header.frame_id;
            poseMsg.header.stamp = msg->header.stamp;
            pose_pub.publish(poseMsg);

            geometry_msgs::TransformStamped transformMsg;
            tf::transformStampedTFToMsg(stampedTransform, transformMsg);
            transform_pub.publish(transformMsg);

            geometry_msgs::Vector3Stamped positionMsg;
            positionMsg.header = transformMsg.header;
            positionMsg.vector = transformMsg.transform.translation;
            position_pub.publish(positionMsg);

            if(image_pub.getNumSubscribers() > 0)
            {
              //show input with augmented information
              cv_bridge::CvImage out_msg;
              out_msg.header.frame_id = msg->header.frame_id;
              out_msg.header.stamp = msg->header.stamp;
              out_msg.encoding = sensor_msgs::image_encodings::RGB8;
              out_msg.image = resultImg;
              image_pub.publish(out_msg.toImageMsg());
            }

            if(debug_pub.getNumSubscribers() > 0)
            {
              //show also the internal image resulting from the threshold operation
              cv_bridge::CvImage debug_msg;
              debug_msg.header.frame_id = msg->header.frame_id;
              debug_msg.header.stamp = msg->header.stamp;
              debug_msg.encoding = sensor_msgs::image_encodings::MONO8;
              debug_msg.image = MDetector.getThresholdedImage();
              debug_pub.publish(debug_msg.toImageMsg());
            }
          }
        }
			}
			catch (cv_bridge::Exception& e)
			{
				ROS_ERROR("cv_bridge exception: %s", e.what());
				return;
			}
		}

		// wait for one camerainfo, then shut down that subscriber
		void cam_info_callback(const sensor_msgs::CameraInfo &msg)
		{
			camParam = ar_sys::getCamParams(msg, useRectifiedImages);
			cam_info_received = true;
			cam_info_sub.shutdown();
		}
};


int main(int argc,char **argv)
{
	ros::init(argc, argv, "ar_single_board");

	ArSysSingleBoard node;

	ros::spin();
}
