
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>

#include <rviz/ogre_helpers/arrow.h>
#include "landmark_visual.h"

namespace rviz_plugin_tutorials {
    
    LandmarkVisual::LandmarkVisual( Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node ) {
        scene_manager_ = scene_manager;
        frame_node_ = parent_node->createChildSceneNode();
        acceleration_arrow_.reset(new rviz::Arrow( scene_manager_, frame_node_ ));
    }

    LandmarkVisual::~LandmarkVisual() {
        scene_manager_->destroySceneNode(frame_node_);
    }

    void LandmarkVisual::setMessage(const efr_msgs::Landmark::ConstPtr& msg) {
        const geometry_msgs::Point& a = msg->position;

        // resources: https://github.com/team-vigir/vigir_rviz/tree/master/src/rviz/ogre_helpers
        Ogre::Vector3 p( a.x, a.y, a.z );
        acceleration_arrow_->setPosition( p );
        acceleration_arrow_->setDirection(Ogre::Vector3(0,0,1));
        acceleration_arrow_->setScale(Ogre::Vector3(1,1,1));
    }

    void LandmarkVisual::setFramePosition(const Ogre::Vector3& position) {
        frame_node_->setPosition(position);
    }

    void LandmarkVisual::setFrameOrientation(const Ogre::Quaternion& orientation) {
        frame_node_->setOrientation(orientation);
    }

    void LandmarkVisual::setColor(float r, float g, float b, float a) {
        acceleration_arrow_->setColor(r,g,b,a);
    }

}