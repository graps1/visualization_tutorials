#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>

#include <tf/transform_listener.h>

#include <rviz/visualization_manager.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/float_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/frame_manager.h>

#include <efr_msgs/Landmark.h>

#include "landmark_visual.h"
#include "stamped_landmark_list_display.h"

namespace rviz_plugin_tutorials {

    StampedLandmarkListDisplay::StampedLandmarkListDisplay() {}

    StampedLandmarkListDisplay::~StampedLandmarkListDisplay() {}

    void StampedLandmarkListDisplay::onInitialize() {
        MFDClass::onInitialize();
    }

    void StampedLandmarkListDisplay::reset() {
        MFDClass::reset();
    }

    void StampedLandmarkListDisplay::processMessage(const efr_msgs::StampedLandmarkList::ConstPtr& msg) {
        Ogre::Quaternion orientation;
        Ogre::Vector3 position;

        // error handling
        if (!context_->getFrameManager()->getTransform(
            msg->header.frame_id,
            msg->header.stamp,
            position, orientation
        )) {
            ROS_DEBUG("Error transforming from frame '%s' to frame '%s'",
            msg->header.frame_id.c_str(), qPrintable(fixed_frame_));
            return;
        }

        visuals_.clear();
        
        for (int i=0; i<msg->landmarks.size(); i++) {
            const boost::shared_ptr<const efr_msgs::Landmark> lm( new efr_msgs::Landmark(msg->landmarks[i]) );
            // const efr_msgs::Landmark& lm = msg->landmarks[i];
            // reset visual
            boost::shared_ptr<LandmarkVisual> v (new LandmarkVisual(context_->getSceneManager(), scene_node_));
            // update new visual
            v->setMessage(lm);
            v->setFramePosition(position);
            v->setFrameOrientation(orientation);
            // visuals_.push_back(v);;
            visuals_.push_back(v);
        }
    }

}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_plugin_tutorials::StampedLandmarkListDisplay, rviz::Display)