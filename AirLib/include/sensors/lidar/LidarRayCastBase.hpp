// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_LidarRayCastBase_hpp
#define msr_airlib_LidarRayCastBase_hpp


#include "sensors/lidar/LidarBase.hpp"

namespace msr {
    namespace airlib {

        class LidarRayCastBase : public LidarBase {
        public:
            virtual void getRayCast() = 0;
        };

    }
} //namespace
#endif 