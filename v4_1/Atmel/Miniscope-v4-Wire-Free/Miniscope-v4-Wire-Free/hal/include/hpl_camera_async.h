/**
 * \file
 *
 * \brief Camera interface related functionality declaration.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
#ifndef _HPL_CAMERA_ASYNC_H_INCLUDED
#define _HPL_CAMERA_ASYNC_H_INCLUDED

#include <compiler.h>
#include "hpl_irq.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Camera sensor sync device structure
 *
 * Camera sensor device structure forward declaration.
 */
struct _camera_async_device;

/**
 * \brief Camera sensor callback type
 *.
 * \param[in] descr Camera sensor descriptor
 * \param[in] ch Camera channel number
 */
typedef void (*_camera_async_cb_t)(struct _camera_async_device *device, uint32_t ch);

/**
 * \brief Camera sensor device
 */
struct _camera_async_device {
	_camera_async_cb_t     capture_done;
	struct _irq_descriptor irq;
	void *                 hw;
};

/**
 * \brief Initialize synchronous camera sensor.
 *
 * This function does low level camera sensor configuration.
 *
 * \param[in] device The pointer to device instance
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialization status
 */
void _camera_async_init(struct _camera_async_device *const device, void *const hw);

/**
 * \brief Deinitialize camera sensor.
 *
 * \param[in] device The pointer to device instance
 */
void _camera_async_deinit(struct _camera_async_device *const device);

/**
 * \brief Enable camera sensor
 *
 * \param[in] device The pointer to device instance
 */
void _camera_async_enable(struct _camera_async_device *const device);

/**
 * \brief Disable camera sensor
 *
 * \param[in] device The pointer to device instance
 */
void _camera_async_disable(struct _camera_async_device *const device);

/**
 * \brief Start camera data capture
 *
 * \param[in] device The pointer to device instance
 * \param[in] ch Capture channel
 * \param[in] buf pointer to frame buffer
 */
void _camera_async_capture_start(struct _camera_async_device *const device, uint32_t ch, uint32_t *buf);

#ifdef __cplusplus
}
#endif

#endif
