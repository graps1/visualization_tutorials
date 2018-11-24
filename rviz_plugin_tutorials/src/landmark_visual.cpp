
#include <OGRE/OgreVector3.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreSceneManager.h>

#include <tf2/LinearMath/Quaternion.h>
#include <rviz/ogre_helpers/shape.h>
#include "landmark_visual.h"

namespace rviz_plugin_tutorials {
    
    LandmarkVisual::LandmarkVisual( Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node ) {
        scene_manager_ = scene_manager;
        frame_node_ = parent_node->createChildSceneNode();
        shape_.reset(new rviz::Shape( rviz::Shape::Cone, scene_manager_, frame_node_ ));
    }

    LandmarkVisual::~LandmarkVisual() {
        scene_manager_->destroySceneNode(frame_node_);
    }

    void LandmarkVisual::setMessage(const efr_msgs::Landmark::ConstPtr& msg) {
        const geometry_msgs::Point& a = msg->position;

        //RIGHT Cone
        if (msg->type.data == 1) {
            setColor(0,0,1,1);
        } 
        //LEFT Cone
        else if (msg->type.data == 2) {
            setColor(1,1,0,1);
        }

        // resources: https://github.com/team-vigir/vigir_rviz/tree/master/src/rviz/ogre_helpers
        Ogre::Vector3 p( a.x, a.y, a.z + 0.14);
        shape_->setPosition( p );
        shape_->setOrientation(Ogre::Quaternion(.707,.707,0,0));
        shape_->setScale(Ogre::Vector3(0.3,0.5,0.3));
    }

    void LandmarkVisual::setFramePosition(const Ogre::Vector3& position) {
        frame_node_->setPosition(position);
    }

    void LandmarkVisual::setFrameOrientation(const Ogre::Quaternion& orientation) {
        frame_node_->setOrientation(orientation);
    }

    void LandmarkVisual::setColor(float r, float g, float b, float a) {
        shape_->setColor(r,g,b,a);
    }

}