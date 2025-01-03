/********************************************************************************************************
 * @file    resolvelist.h
 *
 * @brief   This is the header file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#ifndef LL_RESOLVELIST_H_
#define LL_RESOLVELIST_H_






/**
 * @brief      This function is used to add a device to resolving list
 *             attention: maximum device number in Resolving List is 4 by default. Please contact Telink if this number can not meet your requirement.
 * @param[in]  peerIdAddrType - Peer_Identity_Address_Type
 * @param[in]  peerIdAddr - Peer_Identity_Address
 * @param[in]  peer_irk - peer IRK
 * @param[in]  local_irk - local IRK
 * @return     Status - 0x00: command succeeded;
 *					    Others: command failed, refer to definition of "ble_sts_t" to know the reason
 */
ble_sts_t	blc_ll_addDeviceToResolvingList(ida_type_t peerIdAddrType, u8 *peerIdAddr, u8 *peer_irk, u8 *local_irk);


/**
 * @brief      This function is used to remove a device from resolving list
 * 			   Please refer to BLE Core Specification: Vol 4, Part E, 7.8.39 for more information to understand the meaning of each parameters and
 * 			   the return values.
 * @param[in]  peerIdAddrType - Peer_Identity_Address_Type
 * @param[in]  peerIdAddr - Peer_Identity_Address
 * @return     Status - 0x00: command succeeded;
 *					    Others: command failed, refer to definition of "ble_sts_t" to know the reason
 */
ble_sts_t	blc_ll_removeDeviceFromResolvingList(ida_type_t peerIdAddrType, u8 *peerIdAddr);


/**
 * @brief      This function is used to reset resolving list
 * @param[in]  none
 * @return     Status - 0x00: command succeeded;
 *					    Others: command failed, refer to definition of "ble_sts_t" to know the reason
 */
ble_sts_t	blc_ll_clearResolvingList(void);


/**
 * @brief      This function is used to read resolving list size
 * @param[in]  none
 * @return     resolving list size
 */
int			blc_ll_readResolvingListSize(void);


/**
 * @brief	   This function is used to enable resolution of Resolvable Private Addresses in the Controller.
 * @param[in]  resolution_en - Address Resolution Enable/Disable
 * @return	   Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t	blc_ll_setAddressResolutionEnable (addr_res_en_t resolution_en);


/*
 * @brief 	   This function is used to set the length of time the controller uses a
 * 			   Resolvable Private Address before a new resolvable	private address is
 * 			   generated and starts being used. This timeout applies to all addresses
 * 			   generated by the controller
 * 			   Please refer to BLE Core Specification: Vol 4, Part E, 7.8.45 for more information to understand the meaning of each parameters and
 * 			   the return values.
 * @param[in]  rpa_timeout_s - RPA_Timeout: RPA_Timeout measured in seconds Range: 1 to 3600, Time range: 1 s to 1 hour
 * @return	   Status - 0x00: command succeeded;
 *				        Others: command failed, refer to definition of "ble_sts_t" to know the reason
 */
ble_sts_t  		blc_ll_setResolvablePrivateAddressTimeout (u16 rpa_timeout_s);


/*
 * @brief 	   This function is used to allow the Host to specify the privacy mode to be used for a given entry on the resolving list.
 * @param[in]  peerIdAddrType - Peer Identity Address Type
 * @param[in]  peerIdAddr - Peer Identity Address
 * @param[in]  privMode - Privacy_Mode: Network/Device Privacy Mode
 * @return	   Status - 0x00: command succeeded;
 *					    Others: command failed, refer to definition of "ble_sts_t" to know the reason
 */
ble_sts_t  		blc_ll_setPrivacyMode(ida_type_t peerIdAddrType, u8* peerIdAddr, privacy_mode_t privMode);



#endif /* LL_RESOLVELIST_H_ */
