// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.


#ifndef msr_airlib_SimpleLidar_hpp
#define msr_airlib_SimpleLidar_hpp

#include "common/Common.hpp"
#include "LidarSimpleParams.hpp"
#include "LidarBase.hpp"

namespace msr {
    namespace airlib {

        class LidarSimple : public LidarBase {
        public:
            //constructors
            LidarSimple(const LidarSimpleParams& params = LidarSimpleParams())
                : params_(params)
            {
                point_density = params_.point_density;
                field_of_view = params_.field_of_view;
                flight_line_overlap = params_.flight_line_overlap;
                altitude_above_ground = params_.altitude_above_ground;
            }

            //*** Start: UpdatableState implementation ***//
            virtual void reset() override
            {
                LidarBase::reset();

                last_time_ = clock()->nowNanos();
                point_density.reset();
                state_.gyroscope_bias = params_.gyro.turn_on_bias;
                state_.accelerometer_bias = params_.accel.turn_on_bias;
                gauss_dist.reset();
                updateOutput();
            }

            virtual void update() override
            {
                LidarBase::update();

                updateOutput();
            }
            //*** End: UpdatableState implementation ***//

            virtual ~LidarSimple() = default;

        private: //methods
            void updateOutput()
            {
                Output output;
                const GroundTruth& ground_truth = getGroundTruth();

                output.angular_velocity = ground_truth.kinematics->twist.angular;
                output.linear_acceleration = ground_truth.kinematics->accelerations.linear - ground_truth.environment->getState().gravity;
                output.orientation = ground_truth.kinematics->pose.orientation;

                //acceleration is in world frame so transform to body frame
                output.linear_acceleration = VectorMath::transformToBodyFrame(output.linear_acceleration,
                    ground_truth.kinematics->pose.orientation, true);

                //add noise
                addNoise(output.linear_acceleration, output.angular_velocity);
                // TODO: Add noise in orientation?

                setOutput(output);
            }

            void addNoise()
            {

            }


        private: //fields
            LidarSimpleParams params_;
            RandomVectorGaussianR gauss_dist = RandomVectorGaussianR(0, 1);

            //cached calculated values
            real_T point_density, field_of_view, flight_line_overlap, altitude_above_ground;

            struct State {
                Vector3r gyroscope_bias;
                Vector3r accelerometer_bias;
            } state_;

            TTimePoint last_time_;
        };


    }
} //namespace
#endif
