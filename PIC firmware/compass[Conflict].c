/*
 * This file deals with both the compass on the main board as well
 * as the compass on the pixy sub-board. The one we care about
 * a lot is the one on the pixy because it will give us our
 * angle measurment of the pixy. The information
 *
 * 00     Configuration Reg. A         R/W
 * 01     Configuration Reg. B         R/W
 * 02     Mode Register                R/W
 * 03     Data Output X MSB Reg.       R
 * 04     Data Output X LSB Reg.       R
 * 05     Data Output Z MSB Reg.       R
 * 06     Data Output Z LSB Reg.       R
 * 07     Data Output Y MSB Reg.       R
 * 08     Data Output Y LSB Reg.       R
 * 09     Status Reg.                  R
 * 10     Identification Reg. A        R
 * 11     Identification Reg. B        R
 * 12     Identification Reg. C        R
 *
 *
 *
 * Address: 0x1E
 *
 * Note:
 *
 * To minimize the communication between the master and this
 * device, the address pointer updated automatically without
 * master intervention. The register pointer will be
 * incremented by 1 automatically after the current register
 * has been read successfully.
 *
 * Any attempt to read an invalid address location returns 0?s,
 * and any write to an invalid address location or an undefined
 * bit within a valid address location is ignored by this device.
 *
 *
 */