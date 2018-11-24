#ifndef LANDMARK_VISUAL_H
#define LANDMARK_VISUAL_H

#include <efr_msgs/Landmark.h>

namespace Ogre {
    class Vector3;
    class Quaternion;
}

namespace rviz {
    class Arrow;
}

namespace rviz_plugin_tutorials {
    class LandmarkVisual {
        public:
            LandmarkVisual(Ogre::SceneManager* scene_manager, Ogre::SceneNode* parent_node);
            virtual ~LandmarkVisual();
            void setMessage(const efr_msgs::Landmark::ConstPtr& msg);

            void setFramePosition(const Ogre::Vector3& position);
            void setFrameOrientation(const Ogre::Quaternion& orientation);
            void setColor(float r, float g, float b, float a);
        private:
            boost::shared_ptr<rviz::Arrow> acceleration_arrow_;
            Ogre::SceneNode* frame_node_;
            Ogre::SceneManager* scene_manager_;
    };    
}

#endif