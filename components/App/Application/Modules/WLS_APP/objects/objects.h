/*
 * Copyright 2021-2024 AVSystem <avsystem@avsystem.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdbool.h>
#include "i_wireless_data.h"
#include <anjay/anjay.h>
#include <anjay/dm.h>
#include <anjay/lwm2m_send.h>

#define OBJ_IID 0

#ifdef BASIC
#define MAX_TIME_INSTANCES 2
#define MAX_BINARY_INSTANCES 1
#define MAX_PERCENTAGE_INTANCES 0
#endif

#ifdef ADVANCED
#define MAX_TIME_INSTANCES 4
#define MAX_BINARY_INSTANCES 4
#define MAX_PERCENTAGE_INTANCES 3
#endif

const anjay_dm_object_def_t **plant_data_object_create(void);
void plant_object_release(const anjay_dm_object_def_t **def);
void plant_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);
void plant_object_value_update(uint32_t plant_data,const anjay_dm_object_def_t *const *def);
void plant_object_send(anjay_send_batch_builder_t *builder,anjay_t *anjay, const anjay_dm_object_def_t **def);

const anjay_dm_object_def_t **device_object_create(void);
void device_object_release(const anjay_dm_object_def_t **def);
void device_object_update(anjay_t *anjay,
                          const anjay_dm_object_def_t *const *def);
void device_object_time_update(int64_t current_time,const anjay_dm_object_def_t *const *def);

const anjay_dm_object_def_t **time_object_create(void);
void time_object_release(const anjay_dm_object_def_t **def);
void time_object_value_update(int64_t *time_data,const anjay_dm_object_def_t *const *def);
void time_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);

const anjay_dm_object_def_t **percentage_object_create(void);
void percentage_object_release(const anjay_dm_object_def_t **def);
void percentage_object_value_update(float *per_data,const anjay_dm_object_def_t *const *def);
void percentage_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);

const anjay_dm_object_def_t **temperature_object_create(void);
void temperature_object_release(const anjay_dm_object_def_t **def);
void temperature_object_value_update(float temperature_data,const anjay_dm_object_def_t *const *def);
void temperature_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);

const anjay_dm_object_def_t **air_moist_object_create(void);
void air_moist_object_release(const anjay_dm_object_def_t **def);
void air_moist_object_value_update(float air_moist_data,const anjay_dm_object_def_t *const *def);
void air_moist_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);

const anjay_dm_object_def_t **accelerometer_data_object_create(void);
void accelerometer_object_release(const anjay_dm_object_def_t **def);
void accelerometer_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);
void accelerometer_object_value_update(float x, float y, float z,const anjay_dm_object_def_t *const *def);
void accelerometer_object_send(anjay_send_batch_builder_t *builder,anjay_t *anjay, const anjay_dm_object_def_t **def);

const anjay_dm_object_def_t **binary_object_create(void);
void binary_object_release(const anjay_dm_object_def_t **def);
void binary_object_value_update(uint8_t (*binary_data)[DATA_BUFFER_SIZE*4],const anjay_dm_object_def_t *const *def);
void binary_object_update(anjay_t *anjay,const anjay_dm_object_def_t *const *def);