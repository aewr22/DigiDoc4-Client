/*
 * QDigiDocClient
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#pragma once

#include "QPKCS11.h"

#include "pkcs11.h"

#include <QtCore/QLibrary>
#include <QtCore/QThread>

class QPKCS11Private: public QThread
{
	Q_OBJECT
public:
	QByteArray attribute( CK_SESSION_HANDLE session, CK_OBJECT_HANDLE obj, CK_ATTRIBUTE_TYPE type ) const;
	QVector<CK_OBJECT_HANDLE> findObject( CK_SESSION_HANDLE session, CK_OBJECT_CLASS cls ) const;
	QVector<CK_SLOT_ID> slotIds( bool token_present ) const;
	void updateTokenFlags( TokenData &t, CK_ULONG f ) const;

	static CK_RV createMutex( CK_VOID_PTR_PTR mutex );
	static CK_RV destroyMutex( CK_VOID_PTR mutex );
	static CK_RV lockMutex( CK_VOID_PTR mutex );
	static CK_RV unlockMutex( CK_VOID_PTR mutex );

	QLibrary		lib;
	CK_FUNCTION_LIST_PTR f = nullptr;
	CK_SESSION_HANDLE session = 0;
	CK_ULONG_PTR	certIndex = nullptr;

	void run();
	CK_RV result = CKR_OK;
};
