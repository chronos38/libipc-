/*  This file is part of libipc++
 *
 *  Copyright (C) 2014 David Wolf, Leonhardt Schwarz
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef LIBIPC_MESSAGEQUEUE_H
#define LIBIPC_MESSAGEQUEUE_H

#ifdef _MSC_VER
#pragma once
#endif

#include "Exception/MessageQueueException.h"

#ifdef SendMessage
#undef SendMessage
#endif

#ifdef ReceiveMessage
#undef ReceiveMessage
#endif

namespace ipc {
#ifdef _MSC_VER
    typedef long PriorityId; // TODO: long durch Win32 Datentyp ersetzen
#else
    typedef long PriorityId;
#endif

    struct Message {
        PriorityId Priority;
        std::vector<char> Data;
    };

    // TODO: Ein IO Interace für Schreib- und Leseoperationen definieren.

    /*!
     * This class encapsulates the OS message queue interface.
     */
    class LIBIPC_API MessageQueue : public ReferenceType
    {
    public:
        /*!
         * Creates a new message queue with given file name. If this
         * constructor fails, it throws an exception providing information
         * about the error.
         *
         * \param[in]   fileName    File name for the message queue.
         */
        MessageQueue(const std::string& fileName) throw(MessageQueueException);
        virtual ~MessageQueue();

        /*!
         * Send a message to the queue. If an error happend while sending or
         * the message could not be sent. Than an exception is raised.
         *
         * \param[in]   message Message to send to the queue.
         */
        void SendMessage(const Message& message) throw(MessageQueueException);

        /*!
         * Reads a message from the queue. If there is no message, than this
         * method blocks until a message is received.
         *
         * \param[out]  message The received message.
         * \returns Also returns the received message.
         */
        Message& ReceiveMessage(Message& message) throw(MessageQueueException);

        /*!
         * Reads only a message with given ID from the queue. If the queue
         * contains no such message, than this method returns immediately. In
         * that case the return value is an empty message. In any other case a 
         * valid message is returned.
         *
         * \param[out]  message The received message.
         * \param[in]   id      The required ID for the message.
         * \returns Also returns the received message or a nullptr if no such
         *          message is in the queue.
         */
        Message& ReceiveMessage(Message& message, PriorityId id) throw(MessageQueueException);
    };
}

#endif
