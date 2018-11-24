#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>

#include <tf/transform_listener.h>

#include <rviz/visualization_manager.h>
#include <rviz/properties/color_property.h>
#include <rviz/properties/float_property.h>
#include <rviz/properties/int_property.h>
#include <rviz/frame_manager.h>

#include "landmark_visual.h"
#include "landmark_display.h"

namespace rviz_plugin_tutorials {

    LandmarkDisplay::LandmarkDisplay() {
        color_property_ = new rviz::ColorProperty("Color", QColor(204, 51, 204),
        "Color to draw the acceleration arrow", this, SLOT(updateColorAndAlpha()));
        alpha_property_ = new rviz::FloatProperty("Alpha", 1.0, "0 is fully transparent",
        this, SLOT(updateColorAndAlpha()));
    }

    LandmarkDisplay::~LandmarkDisplay() {}

    void LandmarkDisplay::onInitialize() {
        MFDClass::onInitialize();
    }

    void LandmarkDisplay::reset() {
        MFDClass::reset();
    }

    void LandmarkDisplay::updateColorAndAlpha() {
        float alpha = alpha_property_->getFloat();
        Ogre::ColourValue color = color_property_->getOgreColor();
        visual_->setColor(color.r, color.g, color.b, color.a);
    }

    void LandmarkDisplay::processMessage(const efr_msgs::Landmark::ConstPtr& msg) {
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

        // reset visual
        visual_.reset(new LandmarkVisual(context_->getSceneManager(), scene_node_));
        
        // update new visual
        visual_->setMessage(msg);
        visual_->setFramePosition(position);
        visual_->setFrameOrientation(orientation);

        updateColorAndAlpha();
    }

}

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_plugin_tutorials::LandmarkDisplay, rviz::Display)