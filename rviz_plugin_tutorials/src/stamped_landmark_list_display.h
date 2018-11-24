#ifndef STAMPED_LANDMARK_LIST_DISPLAY_H
#define STAMPED_LANDMARK_LIST_DISPLAY_H

#ifndef Q_MOC_RUN
#include <rviz/message_filter_display.h>
#include <efr_msgs/StampedLandmarkList.h>
#endif

namespace Ogre {
    class SceneNode;
}

namespace rviz_plugin_tutorials {

    class LandmarkVisual;
    
    class StampedLandmarkListDisplay : public rviz::MessageFilterDisplay<efr_msgs::StampedLandmarkList> {
        Q_OBJECT
        public:
            StampedLandmarkListDisplay();
            virtual ~StampedLandmarkListDisplay();

        protected:
            virtual void onInitialize();
            virtual void reset();

        private:
            void processMessage(const efr_msgs::StampedLandmarkList::ConstPtr& msg);
            std::vector< boost::shared_ptr<LandmarkVisual> > visuals_;
    };

}


#endif // !STAMPED_LANDMARK_LIST_DISPLAY_H
