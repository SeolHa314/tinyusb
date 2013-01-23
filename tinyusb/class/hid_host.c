/*
 * hid_host.c
 *
 *  Created on: Dec 20, 2012
 *      Author: hathach
 */

/*
 * Software License Agreement (BSD License)
 * Copyright (c) 2012, hathach (tinyusb.net)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the tiny usb stack.
 */

#include "common/common.h"

#if defined TUSB_CFG_HOST && defined DEVICE_CLASS_HID

#include "hid_host.h"

tusb_error_t tusbh_keyboard_get(tusb_handle_device_t const device_hdl, tusb_keyboard_report_t * const report)
{
  usbh_device_info_t *p_device_info;

  pipe_handle_t pipe_in;
  osal_queue_id_t qid;

  ASSERT_PTR(report, TUSB_ERROR_INVALID_PARA);
  p_device_info = usbh_device_info_get(device_hdl);
  ASSERT_PTR(p_device_info, TUSB_ERROR_INVALID_PARA);

  pipe_in = p_device_info->configuration.classes.hid_keyboard.pipe_in;
  qid     = p_device_info->configuration.classes.hid_keyboard.qid;

  ASSERT(0 != pipe_in, TUSB_ERROR_CLASS_DEVICE_DONT_SUPPORT);
  ASSERT_STATUS( osal_queue_get(qid, (uint32_t*)report, OSAL_TIMEOUT_WAIT_FOREVER) );
  ASSERT_STATUS( osal_queue_get(qid, ((uint32_t*)report)+1, OSAL_TIMEOUT_WAIT_FOREVER) );

  return TUSB_ERROR_NONE;
}

#endif
