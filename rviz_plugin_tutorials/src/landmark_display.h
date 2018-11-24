#ifndef LANDMARK_DISPLAY_H
#define LANDMARK_DISPLAY_H

#ifndef Q_MOC_RUN
#include <rviz/message_filter_display.h>
#include <efr_msgs/Landmark.h>
#endif

namespace Ogre {
    class SceneNode;
}

namespace rviz {
    class ColorProperty;
    class FloatProperty;
    class IntProperty;
}

namespace rviz_plugin_tutorials {

    class LandmarkVisual;
    
    class LandmarkDisplay : public rviz::MessageFilterDisplay<efr_msgs::Landmark> {
        Q_OBJECT
        public:
            LandmarkDisplay();
            virtual ~LandmarkDisplay();

        protected:
            virtual void onInitialize();
            virtual void reset();

        private Q_SLOTS:
            void updateColorAndAlpha();

        private:
            void processMessage(const efr_msgs::Landmark::ConstPtr& msg);
            boost::shared_ptr<LandmarkVisual> visual_;

            rviz::ColorProperty* color_property_;
            rviz::FloatProperty* alpha_property_;
    };

}

#endif
