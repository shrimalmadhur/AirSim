// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_LidarBase_hpp
#define msr_airlib_LidarBase_hpp


#include "sensors/SensorBase.hpp"


namespace msr {
    namespace airlib {

        class LidarBase : public SensorBase {
        public: //types
            struct Output {	//structure is same as ROS LaserScan message http://wiki.ros.org/navigation/Tutorials/RobotSetup/Sensors
                real_T angle_min;
                real_T angle_max;
                real_T angle_increment;
                real_T time_increment;
                real_T scan_time;
                real_T range_min;
                real_T range_max;
                vector<real_T> ranges;
                vector<real_T> intensities;
            };


        public:
            virtual void reportState(StateReporter& reporter) override
            {
                //call base
                UpdatableObject::reportState(reporter);

                reporter.writeValue("angle_min", output_.angle_min);
                reporter.writeValue("angle_max", output_.angle_max);
                reporter.writeValue("angle_increment", output_.angle_increment);
                reporter.writeValue("scan_time", output_.scan_time);
                reporter.writeValue("range_min", output_.range_min);
                reporter.writeValue("range_max", output_.range_max);
                reporter.writeValue("ranges", output_.ranges);
                reporter.writeValue("intensities", output_.intensities);
            }

            const Output& getOutput() const
            {
                return output_;
            }

        protected:
            void setOutput(const Output& output)
            {
                output_ = output;
            }


        private:
            Output output_;
        };


    }
} //namespace
#endif 
