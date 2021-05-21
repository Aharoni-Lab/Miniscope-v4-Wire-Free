/**
 * \file
 *
 * \brief Camera Sensor functionality implementation.
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

#include <hpl_dma.h>
#include <hpl_camera_async.h>
#include <utils_assert.h>
#include <utils.h>
#include <hpl_pcc_config.h>

#define CAMERA_CHN_NUM_MAX 1

/*!< Pointer to hpl device */
static struct _camera_async_device *_pcc_dev = NULL;

struct _dma_resource *resource;
static void           _pcc_dma_transfer_done(struct _dma_resource *resource)
{
	struct _camera_async_device *dev = (struct _camera_async_device *)resource->back;
	dev->capture_done(dev, 0);
}

void _camera_async_init(struct _camera_async_device *const device, void *const hw)
{
	uint32_t data = 0;
	device->hw    = hw;

	data = PCC_MR_CID(0x3) | PCC_MR_ISIZE(CONF_PCC_ISIZE) | CONF_PCC_FRSTS << PCC_MR_FRSTS_Pos
	       | CONF_PCC_HALFS << PCC_MR_HALFS_Pos | CONF_PCC_ALWYS << PCC_MR_ALWYS_Pos
	       | CONF_PCC_SCALE << PCC_MR_SCALE_Pos | PCC_MR_DSIZE(CONF_PCC_DSIZE);
	hri_pcc_write_MR_reg(device->hw, data);

	_pcc_dev = device;

	_dma_get_channel_resource(&resource, CONF_PCC_DMA_CHANNEL);
	resource->back                 = device;
	resource->dma_cb.transfer_done = _pcc_dma_transfer_done;
}

void _camera_async_deinit(struct _camera_async_device *const device)
{
	_camera_async_disable(device->hw);
}

void _camera_async_enable(struct _camera_async_device *const device)
{
	hri_pcc_set_MR_reg(device->hw, PCC_MR_PCEN);
}

void _camera_async_disable(struct _camera_async_device *const device)
{
	hri_pcc_write_MR_reg(device->hw, 0);
}

void _camera_async_capture_start(struct _camera_async_device *const device, uint32_t ch, uint32_t *buf)
{
	if (ch > CAMERA_CHN_NUM_MAX) {
		return;
	}
	_dma_set_irq_state(CONF_PCC_DMA_CHANNEL, DMA_TRANSFER_COMPLETE_CB, true);

	_dma_set_source_address(CONF_PCC_DMA_CHANNEL, (void *)&(((Pcc *)device->hw)->RHR.reg));
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, buf);
	_dma_srcinc_enable(CONF_PCC_DMA_CHANNEL, false);
	_dma_set_data_amount(CONF_PCC_DMA_CHANNEL, CONF_PCC_DMA_FRAME_SIZE);
	_dma_enable_transaction(CONF_PCC_DMA_CHANNEL, false);
}

void PCC_Handler(void)
{
	void *const       hw       = _pcc_dev->hw;
	volatile uint32_t int_mask = hri_pcc_read_ISR_reg(hw);
	hri_pcc_clear_IMR_DRDY_bit(hw);

	if (int_mask & PCC_ISR_DRDY) {
		if (_pcc_dev->capture_done) {
			_pcc_dev->capture_done(_pcc_dev, 0);
		}
	} else {
		return;
	}
}

//@}
