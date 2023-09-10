/**
 * \file
 *
 * \brief Camera Interface functionality declaration.
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

#ifndef HAL_CAMERA_ASYNC_H_INCLUDED
#define HAL_CAMERA_ASYNC_H_INCLUDED

#include <hpl_camera_async.h>
#include <utils_assert.h>
#include <utils.h>
#include <hal_atomic.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_camera_async
 *
 *@{
 */

/**
 * \brief Camera driver version
 */
#define CAMERA_ASYNC_DRIVER_VERSION 0x00000001u

/**
 * \brief Camera sensor synchronous descriptor
 *
 * The Camera sensor descriptor forward declaration.
 */
struct camera_async_descriptor;

/**
 * \brief Camera sensor callback type
 *
 * \param[in] descr Camera sensor descriptor
 * \param[in] ch Camera channel number
 */
typedef void (*camera_async_cb_t)(struct camera_async_descriptor *const descr, uint32_t ch);

/**
 * \brief Camera sensor descriptor
 */
struct camera_async_descriptor {
	/** Camera sensor HPL device descriptor */
	struct _camera_async_device device;
	/** Capture done callback handlers on camera channels */
	camera_async_cb_t capture_done;
};

/**
 * \brief Initialize Camera sensor.
 *
 * This function initializes the given Camera sensor descriptor.
 * It checks if the given hardware is initialized or not and if the given hardware
 * is permitted to be initialized.
 *
 * \param[out] descr The camera sensor descriptor to initialize
 * \param[in] hw The pointer to hardware instance
 *
 * \return Initialization status.
 */
int32_t camera_async_init(struct camera_async_descriptor *const descr, void *const hw);

/**
 * \brief Deinitialize camera sensor.
 *
 * This function deinitializes the given camera sensor descriptor.
 * It checks if the given hardware is initialized and if the given hardware is
 * permitted to be deinitialized.
 *
 * \param[in] descr Camera sensor descriptor to deinitialize
 *
 * \return De-initialization status.
 */
static inline int32_t camera_async_deinit(struct camera_async_descriptor *const descr)
{
	ASSERT(descr);

	_camera_async_deinit(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Enable camera sensor
 *
 * This function enables the camera sensor by the given camera sensor descriptor.
 *
 * \param[in] descr Camera sensor descriptor to enable
 *
 * \return Enabling status.
 */
static inline int32_t camera_async_enable(struct camera_async_descriptor *const descr)
{
	ASSERT(descr);

	_camera_async_enable(&descr->device);

	return ERR_NONE;
}

/**
 * \brief Disable camera sensor
 *
 * This function disables the camera sensor by the given camera sensor descriptor.
 *
 * \param[in] descr The camera sensor descriptor to disable
 *
 * \return Disabling status.
 */
static inline int32_t camera_async_disable(struct camera_async_descriptor *const descr)
{
	ASSERT(descr);

	_camera_async_disable(&descr->device);

	return ERR_NONE;
}

/** \brief Register camera sensor callback.
 *  \param[in] descr Pointer to the HAL descriptor
 *  \param[in] cb   A callback function, passing NULL de-registers callback
 *
 *  \return The status of callback assignment.
 *  \retval ERR_NONE A callback is registered successfully
 *  \retval -1 Passed parameters were invalid
 */
static inline int32_t camera_async_register_callback(struct camera_async_descriptor *const descr, camera_async_cb_t cb)
{
	ASSERT(descr);

	descr->capture_done = cb;

	return ERR_NONE;
}

/**
 * \brief Start camera data capture
 *
 * This function starts capturing camera data.
 *
 * \param[in] descr Camera sensor descriptor
 * \param[in] ch Capture channel
 * \param[in] buf Pointer to frame buffer
 *
 * \note The buffer should be big enough for a frame.
 *
 * \return Capture start status.
 */
static inline int32_t camera_async_capture_start(struct camera_async_descriptor *const descr, uint32_t ch,
                                                 uint32_t *buf)
{
	ASSERT(descr);
	ASSERT(buf);

	_camera_async_capture_start(&descr->device, ch, buf);

	return ERR_NONE;
}

/**
 * \brief Retrieve the current driver version
 *
 * \return Current driver version.
 */
static inline uint32_t camera_async_get_version(void)
{
	return CAMERA_ASYNC_DRIVER_VERSION;
}

	/**@}*/

#ifdef __cplusplus
}
#endif

#endif
