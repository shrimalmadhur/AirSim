// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_LidarSimpleParams_hpp
#define msr_airlib_LidarSimpleParams_hpp

#include "common/Common.hpp"


namespace msr {
    namespace airlib {

        struct LidarSimpleParams {

            // http://felix.rohrba.ch/en/2015/four-essential-lidar-parameters/
            real_T point_density = 100; // 100 pts/m2
            real_T flight_line_overlap = 30; // 30% overlap
            real_T altitude_above_ground = 1.5f; // m

            struct Resolution {
                real_T vertical_resolution;
                real_T horizontal_resolution;
            } resol;

            struct FieldOfView {
                real_T vertical_fov;
                real_T horizontal_fov;
            } field_of_view;
        };

    }
} //namespace
#endif
