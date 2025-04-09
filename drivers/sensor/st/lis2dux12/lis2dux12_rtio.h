/* ST Microelectronics LIS2DUX12 6-axis IMU sensor driver
 *
 * Copyright (c) 2023 Google LLC
 * Copyright (c) 2024 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_LIS2DUX12_RTIO_H_
#define ZEPHYR_DRIVERS_SENSOR_LIS2DUX12_RTIO_H_

#include <zephyr/device.h>
#include <zephyr/rtio/rtio.h>

int lis2dux12_gbias_config(const struct device *dev, enum sensor_channel chan,
			    enum sensor_attribute attr,
			    const struct sensor_value *val);
int lis2dux12_gbias_get_config(const struct device *dev, enum sensor_channel chan,
				enum sensor_attribute attr, struct sensor_value *val);
void lis2dux12_submit(const struct device *sensor, struct rtio_iodev_sqe *iodev_sqe);

void lis2dux12_submit_stream(const struct device *sensor, struct rtio_iodev_sqe *iodev_sqe);
void lis2dux12_stream_irq_handler(const struct device *dev);

#endif /* ZEPHYR_DRIVERS_SENSOR_LIS2DUX12_RTIO_H_ */
