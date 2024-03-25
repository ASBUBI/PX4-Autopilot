/****************************************************************************
 *
 *   Copyright (c) 2023 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#pragma once

// PX4 includes
#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/defines.h>
#include <px4_platform_common/module.h>
#include <px4_platform_common/module_params.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>

// uORB includes
#include <uORB/topics/actuator_outputs.h>
#include <uORB/topics/actuator_motors.h>
#include <uORB/topics/actuator_servos.h>
#include <uORB/PublicationMulti.hpp>
#include <uORB/topics/manual_control_setpoint.h>
#include <uORB/topics/parameter_update.h>
#include <uORB/topics/vehicle_status.h>
#include <uORB/topics/vehicle_control_mode.h>
#include <uORB/Publication.hpp>
#include <uORB/Subscription.hpp>
#include <uORB/SubscriptionMultiArray.hpp>
#include <uORB/topics/differential_drive_setpoint.h>

// Standard library includespr
#include <math.h>

// Local includes
// #include <AckermannDriveKinematics.hpp>
class AckermannDriveControl : public ModuleParams
{
public:
	AckermannDriveControl(ModuleParams *parent);
	~AckermannDriveControl() = default;

	void control();

protected:
	void updateParams() override;

private:

	uORB::Subscription _differential_drive_setpoint_sub{ORB_ID(differential_drive_setpoint)};

	uORB::Publication<differential_drive_setpoint_s> _differential_drive_control_output_pub{ORB_ID(differential_drive_control_output)};
	uORB::Publication<differential_drive_setpoint_s> _differential_drive_setpoint_pub{ORB_ID(differential_drive_setpoint)};

	differential_drive_setpoint_s _differential_drive_setpoint{};

	DEFINE_PARAMETERS(
		(ParamFloat<px4::params::RDD_SPEED_SCALE>) _param_rdd_speed_scale,
		(ParamFloat<px4::params::RDD_ANG_SCALE>) _param_rdd_ang_velocity_scale,
		(ParamFloat<px4::params::RDD_WHEEL_SPEED>) _param_rdd_max_wheel_speed,
		(ParamFloat<px4::params::RDD_WHEEL_BASE>) _param_rdd_wheel_base,
		(ParamFloat<px4::params::RDD_WHEEL_RADIUS>) _param_rdd_wheel_radius,
		(ParamInt<px4::params::CA_R_REV>) _param_r_rev
	)
};
