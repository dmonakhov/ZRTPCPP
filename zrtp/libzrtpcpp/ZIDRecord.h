/*
  Copyright (C) 2006-2010 Werner Dittmann

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _ZIDRECORD_H_
#define _ZIDRECORD_H_

#include <stdint.h>

/**
 * @file ZIDRecord.h
 * @brief ZID cache record management
 *
 * A ZID record stores (caches) ZID (ZRTP ID) specific data that helps ZRTP
 * to achives its key continuity feature. Please refer to the ZRTP
 * specification to get detailed information about the ZID.
 *
 * @ingroup GNU_ZRTP
 * @{
 */

#ifndef __EXPORT
  #if defined _WIN32 || defined __CYGWIN__
    #define __EXPORT    __declspec(dllimport)
    #define __LOCAL
  #elif __GNUC__ >= 4
    #define __EXPORT    __attribute__ ((visibility("default")))
    #define __LOCAL     __attribute__ ((visibility("hidden")))
  #else
    #define __EXPORT
    #define __LOCAL
  #endif
#endif

/**
 * These length are fixed for ZRTP. See RFC 6189.
 */
#define IDENTIFIER_LEN  12
#define RS_LENGTH       32

#if defined(__cplusplus)
/**
 * Interface for classes that implement a ZID cache record.
 *
 * The ZID cache record holds data about a peer. According to ZRTP specification
 * we use a ZID to identify a peer. ZRTP uses the RS (Retained Secret) data
 * to construct shared secrets.
 *
 * @author: Werner Dittmann <Werner.Dittmann@t-online.de>
 */
class __EXPORT ZIDRecord {

public:
    /**
     * Set the @c ZID in the record.
     *
     * Set the ZID in this record before calling read or save.
     */
    virtual void setZid(const unsigned char *zid) =0;

    /**
     * Set @c valid flag in RS1
     */
    virtual void setRs1Valid() =0;

    /**
     * reset @c valid flag in RS1
     */
    virtual void resetRs1Valid()  =0;

    /**
     * Check @c valid flag in RS1
     */
    virtual bool isRs1Valid() =0;

    /**
     * Set @c valid flag in RS2
     */
    virtual void setRs2Valid() =0;

    /**
     * Reset @c valid flag in RS2
     */
    virtual void resetRs2Valid() =0;

    /**
     * Check @c valid flag in RS2
     */
    virtual bool isRs2Valid() =0;

    /**
     * Set MITM key available
     */
    virtual void setMITMKeyAvailable() =0;

    /**
     * Reset MITM key available
     */
    virtual void resetMITMKeyAvailable() =0;

    /**
     * Check MITM key available is set
     */
    virtual bool isMITMKeyAvailable() =0;

    /**
     * Mark this as own ZID record
     */
    virtual void setOwnZIDRecord() =0;

    /**
     * Reset own ZID record marker
     */
    virtual void resetOwnZIDRecord() =0;

    /**
     * Check own ZID record marker
     */
    virtual bool isOwnZIDRecord() =0;

    /**
     * Set SAS for this ZID as verified
     */
    virtual void setSasVerified() =0;

    /**
     * Reset SAS for this ZID as verified
     */
    virtual void resetSasVerified() =0;

    /**
     * Check if SAS for this ZID was verified
     */
    virtual bool isSasVerified() =0;

    /**
     * Return the ZID for this record
     */
    virtual const uint8_t* getIdentifier() =0;

    /**
     * Check if RS1 is still valid
     *
     * Returns true if RS1 is still valid, false otherwise.
     *
     * @return
     *    Returns true is RS1 is not expired (valid), false otherwise.
     */
    virtual bool isRs1NotExpired() =0;

    /**
     * Returns pointer to RS1 data.
     */
    virtual const unsigned char* getRs1() =0;

    /**
     * Check if RS2 is still valid
     *
     * Returns true if RS2 is still valid, false otherwise.
     *
     * @return
     *    Returns true is RS2 is not expired (valid), false otherwise.
     */
    virtual bool isRs2NotExpired() =0;

    /**
     * Returns pointer to RS1 data.
     */
    virtual const unsigned char* getRs2() =0;

    /**
     * Sets new RS1 data and associated expiration value.
     *
     * If the expiration value is >0 or -1 the method stores the new
     * RS1. Before it stores the new RS1 it shifts the exiting RS1
     * into RS2 (together with its expiration time). Then it computes
     * the expiration time of the and stores the result together with
     * the new RS1.
     *
     * If the expiration value is -1 then this RS will never expire.
     *
     * If the expiration value is 0 then the expiration value of a
     * stored RS1 is cleared and no new RS1 value is stored. Also RS2
     * is left unchanged.
     *
     * @param data
     *    Points to the new RS1 data.
     * @param expire
     *    The expiration interval in seconds. Default is -1.
     *
     */
    virtual void setNewRs1(const unsigned char* data, int32_t expire =-1) =0;

    /**
     * Set MiTM key data.
     *
     */
    virtual void setMiTMData(const unsigned char* data) =0;

    /**
     * Get MiTM key data.
     *
     */
    virtual const unsigned char* getMiTMData() =0;
};
#endif /* (__cplusplus) */
#endif
